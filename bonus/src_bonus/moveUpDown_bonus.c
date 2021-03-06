/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moveUpDown_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:33:40 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/07/21 17:34:29 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_up(t_game *game)
{
	float	tmp_x;
	float	tmp_y;

	tmp_x = game->player->x + game->player->dirx * game->player->move_speed;
	tmp_y = game->player->y + game->player->diry * game->player->move_speed;
	if (game->map[(int)tmp_y][(int)tmp_x] == '0')
	{
		game->player->x = tmp_x;
		game->player->y = tmp_y;
	}
}

void	move_down(t_game *game)
{
	float	tmp_x;
	float	tmp_y;

	tmp_x = game->player->x - game->player->dirx * game->player->move_speed;
	tmp_y = game->player->y - game->player->diry * game->player->move_speed;
	if (game->map[(int)tmp_y][(int)tmp_x] == '0')
	{
		game->player->x = tmp_x;
		game->player->y = tmp_y;
	}
}
