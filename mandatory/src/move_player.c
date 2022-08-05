/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:55:30 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/08/05 11:07:19 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_left(t_game *game)
{
	double	tmp_x;
	double	tmp_y;
	double	tmp_dirx;
	double	tmp_diry;

	tmp_dirx = game->player->dirx * cos(1.57)
		- game->player->diry * sin(1.57);
	tmp_diry = game->player->dirx * sin(1.57)
		+ game->player->diry * cos(1.57);
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
	double	tmp_x;
	double	tmp_y;
	double	tmp_dirx;
	double	tmp_diry;

	tmp_dirx = game->player->dirx * -cos(1.57)
		- game->player->diry * -sin(1.57);
	tmp_diry = game->player->dirx * -sin(1.57)
		+ game->player->diry * -cos(1.57);
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
	double	old_dirx;
	double	oldplanex;

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
	double	oldplanex;
	double	old_dirx;

	oldplanex = (double)game->ray->planex;
	old_dirx = game->player->dirx;
	game->player->dirx = game->player->dirx * cos(-game->player->rotation_speed)
		- game->player->diry * sin(-game->player->rotation_speed);
	game->player->diry = old_dirx * sin(-game->player->rotation_speed)
		+ game->player->diry * cos(-game->player->rotation_speed);
	game->ray->planex = game->ray->planex * cos(-game->player->rotation_speed)
		- game->ray->planey * sin(-game->player->rotation_speed);
	game->ray->planey = oldplanex * sin(-game->player->rotation_speed)
		+ game->ray->planey * cos(-game->player->rotation_speed);
}
