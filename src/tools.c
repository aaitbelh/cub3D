#include "../include/cub3d.h"


void TwoDfree(char **table)
{
	int i =0;
	while(table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

void	ft_error_exit(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}