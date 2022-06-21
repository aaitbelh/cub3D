/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:55:30 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/21 15:12:44 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/cub3d.h"
#include <string.h>
#include <math.h>



void move_up(t_game *game)
{
	game->player->x += game->player->DirX * game->player->move_speed;
	game->player->y += game->player->DirY * game->player->move_speed;
}
void move_down(t_game *game)
{
	game->player->x -= game->player->DirX * game->player->move_speed;
	game->player->y -= game->player->DirY * game->player->move_speed;
	
}

void move_left(t_game *game)
{
	float tmp_DirX = game->player->DirX * cos(-1.57) - game->player->DirY * sin(-1.57);
	float tmp_DirY = game->player->DirX * sin(-1.57) + game->player->DirY * cos(-1.57);
	game->player->x += tmp_DirX * game->player->move_speed;
	game->player->y += tmp_DirY * game->player->move_speed;
}

void move_right(t_game *game)
{
	float tmp_DirX= game->player->DirX * cos(1.57) - game->player->DirY * sin(1.57);
	float tmp_DirY = game->player->DirX * sin(1.57) + game->player->DirY * cos(1.57);
	game->player->x += tmp_DirX * game->player->move_speed;
	game->player->y += tmp_DirY * game->player->move_speed;

}
void rotate_right(t_game *game)
{
	float oldDirX = game->player->DirX;
	game->player->DirX = game->player->DirX * cos(game->player->rot_speed) - game->player->DirY * sin(game->player->rot_speed);
	game->player->DirY = oldDirX * sin(game->player->rot_speed) + game->player->DirY * cos(game->player->rot_speed);
	float oldPlaneX = game->player->planeX;
	game->player->planeX = game->player->planeX * cos(game->player->rot_speed) - game->player->planeY * sin(game->player->rot_speed);
	game->player->planeY = oldPlaneX * sin(game->player->rot_speed) + game->player->planeY * cos(game->player->rot_speed);
}
void	rotate_left(t_game *game)
{
	game->player->DirX = game->player->DirX * cos(-game->player->rot_speed) - game->player->DirY * sin(-game->player->rot_speed);
	game->player->DirY = game->player->DirX * sin(-game->player->rot_speed) + game->player->DirY * cos(-game->player->rot_speed);
	float oldDirX = game->player->DirX;
	float oldPlaneX = game->player->planeX;
	game->player->planeX = game->player->planeX * cos(-game->player->rot_speed) - game->player->planeY * sin(-game->player->rot_speed);
	game->player->planeY = oldPlaneX * sin(-game->player->rot_speed) + game->player->planeY * cos(-game->player->rot_speed);
}
