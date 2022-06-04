#include "../include/cub3d.h"

void	ft_error_exit(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}