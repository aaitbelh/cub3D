#include "../include/cub3d.h"


void TwoDfree(char **table)
{
	int i;
	i = 0;
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

int		ft_rgb_to_hex(int r, int g, int b)
{
	int	hex;

	hex = r * 65536 + g * 256 + b;
	return (hex);
}
