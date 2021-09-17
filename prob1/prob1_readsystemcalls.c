#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    char *datainfile;
    int fp, fpsize;

    //allocate memory for datainfile
    datainfile = (char *) calloc(100, sizeof(char));

    //file descriptor opens file
    fp = open("file.txt", O_RDONLY, 0);
    if (fp < 0) {
        perror("r1"); 
        exit(1); 
    }

    //print out what is in file
    fpsize = read(fp, datainfile, 256);
    datainfile[fpsize] = '\0';
    printf("%s\n", datainfile);
}
