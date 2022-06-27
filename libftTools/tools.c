/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:30:13 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/27 09:57:34 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/include/cub3d.h"

void	count_w_h(t_game *game)
{
	int	hight;
	int	width;

	hight = 0;
	width = 0;
	while (game->map[hight][width])
		width++;
	while (game->map[hight])
		hight++;
	game->ply_map->width = width;
	game->ply_map->hight = hight;
}

void	twodfree(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

void	ft_error_exit(char *str)
{
	write (2, str, ft_strlen(str));
	exit(1);
}

int	ft_rgb_to_hex(int r, int g, int b)
{
	int	hex;

	hex = r * 65536 + g * 256 + b;
	return (hex);
}
