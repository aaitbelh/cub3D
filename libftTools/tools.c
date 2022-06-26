/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:30:13 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/26 18:38:15 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/include/cub3d.h"

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
