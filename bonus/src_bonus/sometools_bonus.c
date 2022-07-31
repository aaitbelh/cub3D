/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sometools_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:17:43 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/07/31 09:30:11 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	fix_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == ' ')
				game->map[i][j] = '0';
			j++;
		}
		i++;
	}
}

int	key_released(int key, t_game *game)
{
	game->player->tab[key] = 1;
	if (key == 53)
		exit(0);
	return (1);
}

int	key_pressed(int key, t_game *game)
{
	game->player->tab[key] = 0;
	if(key == 122)
		game->mousestate = !game->mousestate;
	if (key == 53)
		exit(0);
	return (1);
}

int	get_lenght(char **table)
{
	int	tmp;
	int	i;

	tmp = 0;
	tmp = ft_strlen(table[0]);
	i = 1;
	while (table[i])
	{
		if (tmp < ft_strlen(table[i]))
			tmp = ft_strlen(table[i]);
		i++;
	}
	return (tmp);
}
