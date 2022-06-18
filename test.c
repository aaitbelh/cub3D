#include <stdio.h>
#include <string.h>
#include "include/cub3d.h"

int main()
{
	int fd = open("file", O_RDONLY);
	int  i =0;
	char *buf;
	int ret = 1;
	while(1)
	{
		buf = get_next_line(fd);
		if(!buf)
			break;
		if(strstr(buf, "www.netflix.com"))
		{
			printf("%s\n", get_next_line(fd));
			printf("%s\n", get_next_line(fd));
		}
	}
}