For this problem there are three programs.

prob1_write.c is the program to create a new file and write the char
string (datainfile) inside the file that you created. This is compiled
using the make command (look inside make to see specifics). It can be
run using a default command line ./prob1_write

prob1_read.c is the program to read the new file, specifically the
string (datainfile) inside the file that you created. This is compiled
using the make command (look inside make to see specifics). It can be
run using a default command line ./prob1_read

prob1_readsystemcalls.c is the same as the prob1_read except it uses 
system calls to read the file rather than stdio functions.