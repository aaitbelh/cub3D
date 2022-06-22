/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:55:30 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/22 06:00:02 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/cub3d.h"
#include <string.h>
#include <math.h>

void move_up(t_game *game)
{
	float	tmp_x;
	float	tmp_y;

	tmp_x = game->player->x + game->player->dirX * game->player->move_speed;
	tmp_y = game->player->y + game->player->dirY * game->player->move_speed;
	if (game->map[(int)tmp_y][(int)tmp_x] == '0')
	{
		game->player->x = tmp_x;
		game->player->y = tmp_y;
	}
	
}
void move_down(t_game *game)
{
	float	tmp_x;
	float	tmp_y;

	tmp_x = game->player->x - game->player->dirX * game->player->move_speed;
	tmp_y = game->player->y - game->player->dirY * game->player->move_speed;
	if (game->map[(int)tmp_y][(int)tmp_x] == '0')
	{
		game->player->x = tmp_x;
		game->player->y = tmp_y;
	}
}

void	move_left(t_game *game)
{
	float	tmp_x;
	float	tmp_y;
	float	tmp_dirX;
	float	tmp_dirY;

	tmp_dirX = game->player->dirX * cos((M_PI / 2))
		- game->player->dirY * sin((M_PI / 2));
	tmp_dirY = game->player->dirX * sin((M_PI / 2))
		+ game->player->dirY * cos((M_PI / 2));
	tmp_x = game->player->x + tmp_dirX * game->player->move_speed;
	tmp_y = game->player->y + tmp_dirY * game->player->move_speed;
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
	float	tmp_dirX;
	float	tmp_dirY;

	tmp_dirX = game->player->dirX * -cos((M_PI / 2))
		- game->player->dirY * -sin((M_PI / 2));
	tmp_dirY = game->player->dirX * -sin((M_PI / 2))
		+ game->player->dirY * -cos((M_PI / 2));
	tmp_x = game->player->x + tmp_dirX * game->player->move_speed;
	tmp_y = game->player->y + tmp_dirY * game->player->move_speed;
	if (game->map[(int)tmp_y][(int)tmp_x] == '0')
	{
		game->player->x = tmp_x;
		game->player->y = tmp_y;
	}
}

void rotate_left(t_game *game)
{
	float oldDirX = game->player->dirX;
	game->player->dirX = game->player->dirX * cos(game->player->rotation_speed) - game->player->dirY * sin(game->player->rotation_speed);
	game->player->dirY = oldDirX * sin(game->player->rotation_speed) + game->player->dirY * cos(game->player->rotation_speed);
	float oldPlaneX = game->ray->planeX;
	game->ray->planeX = game->ray->planeX * cos(game->player->rotation_speed) - game->ray->planeY * sin(game->player->rotation_speed);
	game->ray->planeY = oldPlaneX * sin(game->player->rotation_speed) + game->ray->planeY * cos(game->player->rotation_speed);
}
void	rotate_right(t_game *game)
{
	game->player->dirX = game->player->dirX * cos(-game->player->rotation_speed) - game->player->dirY * sin(-game->player->rotation_speed);
	game->player->dirY = game->player->dirX * sin(-game->player->rotation_speed) + game->player->dirY * cos(-game->player->rotation_speed);
	//float oldDirX = game->player->dirX;
	float oldPlaneX = game->ray->planeX;
	game->ray->planeX = game->ray->planeX * cos(-game->player->rotation_speed) - game->ray->planeY * sin(-game->player->rotation_speed);
	game->ray->planeY = oldPlaneX * sin(-game->player->rotation_speed) + game->ray->planeY * cos(-game->player->rotation_speed);
}

