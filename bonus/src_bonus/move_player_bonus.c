/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:55:30 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/27 10:43:36 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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
	float oldPlaneX;
	
	oldPlaneX = game->ray->planeX;
	game->player->dirX = game->player->dirX * cos(-game->player->rotation_speed) - game->player->dirY * sin(-game->player->rotation_speed);
	game->player->dirY = game->player->dirX * sin(-game->player->rotation_speed) + game->player->dirY * cos(-game->player->rotation_speed);
	game->ray->planeX = game->ray->planeX * cos(-game->player->rotation_speed) - game->ray->planeY * sin(-game->player->rotation_speed);
	game->ray->planeY = oldPlaneX * sin(-game->player->rotation_speed) + game->ray->planeY * cos(-game->player->rotation_speed);
}

