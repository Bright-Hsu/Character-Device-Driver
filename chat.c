#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t pid,pid1;
    pid=fork();
 
    if (pid<0)
    {
        fprintf(stderr,"fork fail\n");
        return 1;
    }
    else if (pid==0) //child
    {
        system("sudo /home/garrix/code/OS_Lab3/write");
    }
     else  //parent
     {
        system("sudo /home/garrix/code/OS_Lab3/read");
        wait(NULL);
     }
    return 0;

}