#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080 //use port 8080 as said in the problem 2 rubric
  
int main(int argc, char const *argv[]){
  //define variables and structs
  struct sockaddr_in address;
  int client_sock = 0;
  struct sockaddr_in serv_addr;
  char *message = "Network-Centric Programming – Spring 2021 Midterm";
  char buffer[1024] = {0};

  //create socket
  if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
      printf("\n Socket creation failed \n");
      return -1;
  }
  
  //memset
  memset(&serv_addr, '0', sizeof(serv_addr));
  
  //define serv_addr struct parameters
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT); //PORT is defined in the headers as 8080
      
  //convert string to numeric using inet_pton
  //we will use address 127.0.0.1
  if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
      printf("\nConversion not possible or Address does not exist \n");
      return -1;
  }
  
  //connect to the server
  if (connect(client_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
      printf("\nConnection Failed\n");
      return -1;
  }

  //write message inside and print out success message
  write(client_sock, message, strlen(message));
  printf("The message has been sent\n");
  return 0;
}