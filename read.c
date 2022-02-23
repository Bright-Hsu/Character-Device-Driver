#include<sys/types.h>
#include<sys/stat.h> 
#include<stdio.h>
#include<fcntl.h> 
#include<string.h>
#include<unistd.h>

void main(void)
{
	int fd, i;
	pid_t pid=getpid();
	char num[101];
	fd = open("/dev/chardev0", O_RDWR, S_IRUSR | S_IWUSR);
	if (fd != -1)
	{
		while (1)
		{
			for (i = 0; i < 101; i++)
				num[i] = '\0';
			read(fd, num, 100);
			printf("%s\n", num);
			if (strcmp(num, "quit") == 0)
			{
				close(fd);
				break;
			}

		}
	}
	else
	{
		printf("device open failure,%d\n", fd);
	}
}