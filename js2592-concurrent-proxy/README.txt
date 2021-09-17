@author: Jaidev Singh Saberwal

There are two programs.

proxy.c is the concurrent proxy that uses parent and child processes to
handle multiple requests. I got the program working, but for some reason
(not sure why) but it is not recognizing the argument LOCK_SH which is for
shared flock() and it is giving me that red line. Maybe it is just the text editor.

threadproxy.c is the concurrent proxy that usees pthreads and mutex to 
handle multiple clients. This was able to work fine.