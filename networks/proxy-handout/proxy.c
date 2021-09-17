/*
 * proxy.c - A Simple Sequential Web proxy
 *
 * Course Name: 14:332:456-Network Centric Programming
 * Assignment 2
 * Student Name:__Jaidev Singh Saberwal_____
 * 
 * IMPORTANT: This code is an extension of the normal server client requests and 
 * acts as a middleman between the server and the client, forwarding messages to each.
 * We basically forward the requests and responses to each.
 */ 

#include "csapp.h"

//this is the log file
FILE *httplog;

int parse_uri(char *uri, char *target_addr, char *path, int  *port);
void format_log_entry(char *logstring, struct sockaddr_in *sockaddr, char *uri, int size);

/* 
 * main - Main routine for the proxy program 
 */
int main(int argc, char **argv)
{
    int servfd;
    int i, n;
    char hostname[MAXLINE];
    char pathname[MAXLINE];
    int serverport;
    char httpfileentry[MAXLINE];
    char buff[MAXLINE];
    int badreq = 0;
    rio_t rio;
    if (argc != 2) {
	    fprintf(stderr, "Usage: %s <port number>\n", argv[0]);
	    exit(0);
    }

    //listenfd and port define
    int port = atoi(argv[1]);
    int listenfd = open_listenfd(port);

    //log in httpfile
    httplog = fopen("proxy.log", "a");
  
    //client connection wait and accept
    int clientlen, connectionfd, requestlen;
    char *request;
    struct sockaddr_in clientaddr;
    char *requesturi;
    char *requestenduri;
    char *remainingrequest;
    int servresponselen;
    int reqcount = 0;
    while (1) { 
	    badreq = 0;
	    clientlen = sizeof(clientaddr);  
	    connectionfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
        request = (char *)malloc(MAXLINE);
        request[0] = '\0';
        requestlen = 0;
        rio_readinitb(&rio, connectionfd);
        while (1) {
	        if ((n = Rio_readlineb_w(&rio, buff, MAXLINE)) <= 0) {
	            badreq = 1;
	            printf("Bad Request\n");
	            close(connectionfd);
	            free(request);
                break;
	        }

	        if (requestlen + n + 1 > MAXLINE){
                realloc(request, MAXLINE*reqcount++);
            }            
	        strcat(request, buff);
	        requestlen += n;

	        //blank line
	        if (strcmp(buff, "\r\n") == 0){
	            break;
            }
            if (badreq == 1){
                continue;
            }

            //get uri from request
            requesturi = request + 4;
            requestenduri = NULL;
            for (i = 0; i < requestlen; i++) {
	            if (requesturi[i] == ' ') {
	                requesturi[i] = '\0';
	                requestenduri = &requesturi[i];
	                break;
	            }
            }
            //reassert http field is after uri
            if (strncmp(requestenduri + 1, "HTTP/1.0\r\n", strlen("HTTP/1.0\r\n")) && strncmp(requestenduri + 1, "HTTP/1.1\r\n", strlen("HTTP/1.1\r\n"))) {
	            printf("Bad request.\n");
	            close(connectionfd);
	            free(request);
                break;
            }
            remainingrequest = requestenduri + strlen("HTTP/1.0\r\n") + 1;
            
            //parse uri into hostname, pathname, and port
            if (parse_uri(requesturi, hostname, pathname, &serverport) < 0) {
	            printf("Parse inccomplete\n");
                close(connectionfd);
                free(request);
                break;
            }    
            //forward req to server
            if ((servfd = open_clientfd(hostname, serverport)) < 0) {
                printf("Unable to connect.\n");
                free(request);
                break;
            }
            //forward server reply to client
            Rio_readinitb(&rio, servfd);
            servresponselen = 0;
            
            servresponselen += n;
	        printf("Forward request success\n", n);
	        fflush(stdout);
	        bzero(buff, MAXLINE);
        }
        //log requests into httplog
        format_log_entry(httpfileentry, &clientaddr, requesturi, servresponselen);  
        fprintf(httplog, "%s %d\n", httpfileentry, servresponselen);
        fflush(httplog);
        close(servfd);
        close(connectionfd);
        free(request);
    }
}

//simple parsing method to get specific parts of the url
int parse_uri(char *uri, char *hostname, char *pathname, int *port)
{
    char *hoststart;
    char *hostend;
    char *startofpath;
    int len;

    if (strncasecmp(uri, "http://", 7) != 0) {
	    hostname[0] = '\0';
	    return -1;
    }
       
    //get hostname
    hoststart = uri + 7;
    hostend = strpbrk(hoststart, " :/\r\n\0");
    len = hostend - hoststart;
    strncpy(hostname, hoststart, len);
    hostname[len] = '\0';
    
    //get port
    *port = 80;
    if (*hostend == ':'){
        *port = atoi(hostend + 1);
    }
    
    //get path
    startofpath = strchr(hoststart, '/');
    if (startofpath == NULL) {
	    pathname[0] = '\0';
    }
    else {
	    startofpath++;	
	    strcpy(pathname, startofpath);
    }

    return 0;
}
/*
 * format_log_entry - Create a formatted log entry in logstring. 
 * 
 * The inputs are the socket address of the requesting client
 * (sockaddr), the URI from the request (uri), and the size in bytes
 * of the response from the server (size).
 */
void format_log_entry(char *logstring, struct sockaddr_in *sockaddr, 
		      char *uri, int size)
{
    time_t now;
    char time_str[MAXLINE];
    unsigned long host;
    unsigned char a, b, c, d;

    /* Get a formatted time string */
    now = time(NULL);
    strftime(time_str, MAXLINE, "%a %d %b %Y %H:%M:%S %Z", localtime(&now));

    /* 
     * Convert the IP address in network byte order to dotted decimal
     * form. Note that we could have used inet_ntoa, but chose not to
     * because inet_ntoa is a Class 3 thread unsafe function that
     * returns a pointer to a static variable (Ch 13, CS:APP).
     */
    host = ntohl(sockaddr->sin_addr.s_addr);
    a = host >> 24;
    b = (host >> 16) & 0xff;
    c = (host >> 8) & 0xff;
    d = host & 0xff;


    /* Return the formatted log entry string */
    sprintf(logstring, "%s: %d.%d.%d.%d %s", time_str, a, b, c, d, uri);
}


