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
    char buff[256];

    //open the file using fopen
    fp = fopen("file.txt", "r");
    if (fp < 0) { 
        perror("Cannot open file");
        exit(1); 
    }

    //read the data (datainfile) into the file using fwrite
    fseek(fp, 0, SEEK_SET);

    //read and display data
    if (fread(buff, sizeof(buff), 1, fp)<0){ 
        perror("Cannot read data in file");
        exit(1); 
    }

    printf("%s\n", buff);
    fclose(fp);
   
    return(0);
}