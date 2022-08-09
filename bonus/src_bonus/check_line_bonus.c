/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:28:23 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/08/09 16:51:58 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_newline(char *buf, int *lock)
{
	char	*tmp;

	tmp = ft_strtrim(buf, ' ');
	if (tmp[0] == '1' && !*lock)
		*lock = 1;
	if (*lock == 1 && tmp[0] == '\n')
		*lock = 2;
	if (*lock == 2 && tmp[0] == '1')
		*lock = 3;
	free(tmp);
	if (*lock == 3)
		ft_error_exit("a line in the midle of the map\n");
}

void	check_player(t_game *game, int y, int x)
{
	int		lenght;

	lenght = 0;
	while (game->map[y][lenght])
		lenght++;
	if (x == 0 || x == lenght - 1)
		ft_error_exit("error in map not serrundered or space founded\n");
	if (game->map[y][x + 1] == ' ')
		ft_error_exit("error in map not serrundered or space founded\n");
	if (game->map[y][x - 1] == ' ')
		ft_error_exit("error in map not serrundered or space founded\n");
	if (y == 0 || y == game->highofmap - 1)
		ft_error_exit("error in map not serrundered\n");
	if (game->map[y + 1][x] == ' ')
		ft_error_exit("error in map not serrundered or space founded\n");
	if (game->map[y - 1][x] == ' ')
		ft_error_exit("error in map not serrundered or space founded\n");
}
