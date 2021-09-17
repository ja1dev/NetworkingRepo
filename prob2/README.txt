Problem 2 consists of two parts: the server and the client.

prob2_server: prob2_server is the server side of the socket. It is a simple
socket server that uses port 8080 and ip 127.0.0.1. To compile it, run the
makefile provided. To run the program, call ./prob2_server in the terminal
and wait for a signal from the client. Once there is a connection to the
client, it should print out the message that the client sent.

prob2_client: prob2_client is the client side of the socket. It send a
message to the server using a basic socket and port 8080. To compile it, run the
makefile provided. To run the program, call ./prob2_client in a different terminal
from the one used for the server and wait for a signal from the server. 
Once there is a connection to the server is established, client sends message
to the server and it should print out that the message delivered to the server.