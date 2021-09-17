#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main () {

    //define variables for file writing 
    FILE *fp;
    char datainfile[] = "This is a sample text that should be written in the new file";

    //open the file using fopen
    fp = fopen("file.txt", "w+");
    if (fp < 0) { 
        perror("Cannot create file");
        exit(1); 
    }

    //write the data (datainfile) into the file using fwrite
    if (fwrite(datainfile, sizeof(datainfile), 1, fp)<0){
        perror("Cannot write in file");
        exit(1);
    }

   
    return(0);
}