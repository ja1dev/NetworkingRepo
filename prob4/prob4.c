#include <pthread.h> 
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h>

void *thread1(void *arg) { 
    //printf("This is the first created thread.\n"); 
    return ((void *) "This is the first created thread."); 
} 
void *thread2(void *arg) { 
    //printf("This is the second created thread.\n"); 
    return ((void *) "This is the second created thread."); 
} 

int main() 
{ 
    pthread_t thr1,thr2; 
    void *thread_return; 
    printf("This is the main thread.\n");

    //create two threads
    if (pthread_create(&thr1,NULL,thread1,NULL) < 0){
        perror("Thread Creation Failed");
    }
    if (pthread_create(&thr2,NULL,thread2,NULL) < 0){
        perror("Thread Creation Failed");
    }
    //join and print if the thread works within the functions
    if (pthread_join(thr1,&thread_return)<0){
        perror("Join Failed");
    }
    printf("%s\n",(char *)thread_return); 
    if (pthread_join(thr2,&thread_return)<0){
        perror("Join Failed");
    }
    printf("%s\n",(char *)thread_return); 
    exit(0); 
} 