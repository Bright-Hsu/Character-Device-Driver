#include<sys/stat.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#define _WRITE 0
#define _READ  1

int flag = _READ;

int main()
{
    int fd = open("/dev/chardev0",O_RDWR,S_IRUSR | S_IWUSR);
    char msg[101];
    if(fd != -1)
    {
        while(1)
        {
        ROTATE:
            if(flag == _WRITE)
            {
                printf("Process %d, Please send a message:",getpid());
                fgets(msg,101,stdin);
                write(fd,msg,strlen(msg));
                flag = _READ;
            }
            else
            {
                memset(msg,0,101);
                read(fd,msg,101);
                if(strlen(msg) == 0)
                    goto ROTATE;
                printf("Message read from another process:%s",msg);
                flag = _WRITE;
            }
            sleep(1);
        }
    }
    else
        return -1;
}
