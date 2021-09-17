#Sample Makefile. You can make changes to this file according to your need
# The executable must be named proxy

CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -lpthread

OBJS = proxy.o csapp.o threadproxy.c

all: proxy

proxy: $(OBJS)

csapp.o: csapp.c
	$(CC) $(CFLAGS) -c csapp.c

proxy.o: proxy.c
	$(CC) $(CFLAGS) -c proxy.c

threadproxy.o: threadproxy.c
	$(CC) $(CFLAGS) -c threadproxy.c

clean:
	rm -f *~ *.o proxy 

