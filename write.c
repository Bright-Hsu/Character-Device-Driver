#include<sys/types.h> 
#include<sys/stat.h> 
#include<stdio.h> 
#include<stdlib.h>
#include<fcntl.h> 
#include<string.h>
#include<unistd.h>

void main()
{
	pid_t pid=getpid();
	int fd;
	char num[100];

	fd = open("/dev/chardev0", O_RDWR, S_IRUSR | S_IWUSR);
	if (fd != -1)
	{
		while (1)
		{
			printf("Please input the message:\n");
			fgets(num,100,stdin);
			char input[100];
			sprintf(input,"进程%d:%s",pid,num);
			write(fd, input, strlen(input));
			if (strcmp(num, "quit") == 0)
			{
				close(fd);
				break;
			}
		}
	}
	else
	{
		printf("device open failed\n");
	}
}