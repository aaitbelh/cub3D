/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:55:30 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/06 08:44:19 by aaitbelh         ###   ########.fr       */
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

	game->player->move_step = game->player->move_speed;
	tmp_x = game->player->x + cos(game->player->rotation_angle) *  game->player->move_step;
	tmp_y = game->player->y + sin(game->player->rotation_angle) *  game->player->move_step;
	if(game->map[(int)tmp_y][(int)tmp_x] != '1' )
	{
		game->player->x +=  cos(game->player->rotation_angle) *  game->player->move_step;
		game->player->y += sin(game->player->rotation_angle) *  game->player->move_step;
	}
}
void move_down(t_game *game)
{
	float	tmp_x;
	float	tmp_y;

	game->player->move_step = game->player->move_speed;
	tmp_x = game->player->x - cos(game->player->rotation_angle) *  game->player->move_step;
	tmp_y = game->player->y - sin(game->player->rotation_angle) *  game->player->move_step;
	if(game->map[(int)tmp_y][(int)tmp_x] != '1')
	{
		
		game->player->x -=  cos(game->player->rotation_angle) *  game->player->move_step;
		game->player->y -= sin(game->player->rotation_angle) *  game->player->move_step;
	}
	
}
void move_right(t_game *game)
{
	float	tmp_x;
	float	tmp_y;
	int		tmp;

	if(game->player->rotation_angle >= M_PI &&  game->player->rotation_angle <= 2 * M_PI)
		 tmp = 1;
	else
		 tmp = -1;
	game->player->x += cos(M_PI / 2) * tmp;  
	game->player->y += sin(M_PI / 2) * tmp;
}
