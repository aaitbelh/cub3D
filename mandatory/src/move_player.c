/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:55:30 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/07/31 09:40:43 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_left(t_game *game)
{
	double	tmp_x;
	double	tmp_y;
	double	tmp_dirx;
	double	tmp_diry;

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
	double	tmp_x;
	double	tmp_y;
	double	tmp_dirx;
	double	tmp_diry;

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
