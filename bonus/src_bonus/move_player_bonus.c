/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:55:30 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/07/21 14:18:11 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	move_left(t_game *game)
{
	float	tmp_x;
	float	tmp_y;
	float	tmp_dirx;
	float	tmp_diry;

	tmp_dirx = game->player->dirx * cos((M_PI / 2))
		- game->player->diry * sin((M_PI / 2));
	tmp_diry = game->player->dirx * sin((M_PI / 2))
		+ game->player->diry * cos((M_PI / 2));
	tmp_x = game->player->x + tmp_dirx * game->player->move_speed;
	tmp_y = game->player->y + tmp_diry * game->player->move_speed;
	if (game->map[(int)tmp_y][(int)tmp_x] == '0')
	{
		game->player->x = tmp_x;
		game->player->y = tmp_y;
	}
}

void	move_right(t_game *game)
{
	float	tmp_x;
	float	tmp_y;
	float	tmp_dirx;
	float	tmp_diry;

	tmp_dirx = game->player->dirx * -cos((M_PI / 2))
		- game->player->diry * -sin((M_PI / 2));
	tmp_diry = game->player->dirx * -sin((M_PI / 2))
		+ game->player->diry * -cos((M_PI / 2));
	tmp_x = game->player->x + tmp_dirx * game->player->move_speed;
	tmp_y = game->player->y + tmp_diry * game->player->move_speed;
	if (game->map[(int)tmp_y][(int)tmp_x] == '0')
	{
		game->player->x = tmp_x;
		game->player->y = tmp_y;
	}
}

void	rotate_left(t_game *game)
{
	float	old_dirx;
	float	oldplanex;

	oldplanex = game->ray->planex;
	old_dirx = game->player->dirx;
	game->player->dirx = game->player->dirx * cos(game->player->rotation_speed)
		- game->player->diry * sin(game->player->rotation_speed);
	game->player->diry = old_dirx * sin(game->player->rotation_speed)
		+ game->player->diry * cos(game->player->rotation_speed);
	game->ray->planex = game->ray->planex * cos(game->player->rotation_speed)
		- game->ray->planey * sin(game->player->rotation_speed);
	game->ray->planey = oldplanex * sin(game->player->rotation_speed)
		+ game->ray->planey * cos(game->player->rotation_speed);
}

void	rotate_right(t_game *game)
{
	float	oldplanex;

	oldplanex = game->ray->planex;
	game->player->dirx = game->player->dirx * cos(-game->player->rotation_speed)
		- game->player->diry * sin(-game->player->rotation_speed);
	game->player->diry = game->player->dirx * sin(-game->player->rotation_speed)
		+ game->player->diry * cos(-game->player->rotation_speed);
	game->ray->planex = game->ray->planex * cos(-game->player->rotation_speed)
		- game->ray->planey * sin(-game->player->rotation_speed);
	game->ray->planey = oldplanex * sin(-game->player->rotation_speed)
		+ game->ray->planey * cos(-game->player->rotation_speed);
}
