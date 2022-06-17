/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:55:30 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/16 11:12:00 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/cub3d.h"
#include <string.h>
#include <math.h>



void move_up(t_game *game)
{
	int	tmp_x;
	int	tmp_y;

	game->player->move_step = game->player->move_speed;
	tmp_x = game->player->x + cos(game->player->rotation_angle) *  game->player->move_step;
	tmp_y = game->player->y + sin(game->player->rotation_angle) *  game->player->move_step;
	printf("%d %d\n", game->ply_map->hight, tmp_y);
	if(game->map[tmp_y][tmp_x] != '1' && ((tmp_x >= 0 && tmp_x < game->ply_map->width) && (tmp_y > 0 && tmp_y < game->ply_map->hight - 1)))
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
	count_w_h(game);
	if(game->map[(int)tmp_y][(int)tmp_x] != '1' && ((tmp_x >= 0 && tmp_x < game->ply_map->width) && (tmp_y > 0 && tmp_y < game->ply_map->hight - 1)))
	{
		
		game->player->x -=  cos(game->player->rotation_angle) *  game->player->move_step;
		game->player->y -= sin(game->player->rotation_angle) *  game->player->move_step;
	}
	
}
void move_right(t_game *game)
{
	int	tmp_x;
	int	tmp_y;
	
	game->player->move_step = game->player->move_speed;
	tmp_x = game->player->x + cos(game->player->rotation_angle + M_PI_2) *  game->player->move_step;
	tmp_y = game->player->y + sin(game->player->rotation_angle + M_PI_2) *  game->player->move_step;
	if(game->map[(int)tmp_y][(int)tmp_x] != '1' && ((tmp_x >= 0 && tmp_x < game->ply_map->width) && (tmp_y > 0 && tmp_y < game->ply_map->hight - 1)))
	{
		game->player->x += cos(game->player->rotation_angle + M_PI_2) *  game->player->move_step;
		game->player->y += sin(game->player->rotation_angle + M_PI_2) *  game->player->move_step;
	}	
}
void move_left(t_game *game)
{
	float	tmp_x;
	float	tmp_y;

	game->player->move_step = -game->player->move_speed;
	tmp_x = game->player->x + cos(game->player->rotation_angle + M_PI_2) *  game->player->move_step;
	tmp_y = game->player->y + sin(game->player->rotation_angle + M_PI_2) *  game->player->move_step;;
	if(game->map[(int)tmp_y][(int)tmp_x] != '1' && ((tmp_x >= 0 && tmp_x < game->ply_map->width) && (tmp_y >= 0 && tmp_y < game->ply_map->hight - 1)))
	{
		game->player->x += cos(game->player->rotation_angle + M_PI_2) *  game->player->move_step;
		game->player->y += sin(game->player->rotation_angle + M_PI_2) *  game->player->move_step;
	}	
}

