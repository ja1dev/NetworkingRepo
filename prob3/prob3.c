#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    //create child pid
    pid_t child;
    if (child = fork() < 0){
        perror("Process Creation Failed");
    }

    //if child pid is not 0 then we are in the parent process
    if (child != 0) {
        printf("I'm in the parent process\n");
    }

    //if child pid is 0 then we are in the child process
    else {
        printf("I'm in the child process\n");
    }
    return 0;
}