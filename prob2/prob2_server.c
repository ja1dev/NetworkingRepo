#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
    //define variables and structs
    int server_fd, server_sock, valread;
    struct sockaddr_in address;
    int addresslen = sizeof(address);
    char buffer[1024] = {0};
      
    //create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //define struct params
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl (INADDR_ANY);
    address.sin_port = htons( PORT );
      
    //beind socket to port 8080
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    //listen for client
    if (listen(server_fd, 1024) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept request
    if ((server_sock = accept(server_fd, (struct sockaddr *) &address, (socklen_t*) &addresslen))<0){
        perror("accept");
        exit(EXIT_FAILURE);
    }

    //read and print what the client sent
    valread = read(server_sock, buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}