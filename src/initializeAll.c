/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializeAll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 08:39:56 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/21 11:22:54 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void initializeMap(t_game *game)
{
	game->ply_map->C = 0;
	game->ply_map->NO = 0;
	game->ply_map->SE = 0;
	game->ply_map->WE = 0;
	game->ply_map->EA = 0;
	game->ply_map->F = 0;
}

void initializeData(int ac, char **av, t_game *data)
{
	data->ply_map = malloc(sizeof(t_maps));
	data->player = malloc(sizeof(t_player));
	data->line = malloc(sizeof(t_line));
	data->map_name  = ft_strdup(av[ac - 1]);
	data->rays = malloc(sizeof(t_ray) * 1800);
	if(check_map_name(data->map_name))
		ft_error_exit("Wrong Map!\n");
	data->map = read_map(data->map_name);
	initializeMap(data);
	data->player->DirX = -1;
	data->player->DirY = 1;
	data->player->planeX = 0;
	data->player->planeY = 0.66;
	// checkElement(data);
	// check_map(data->map, data);
	// count_w_h(data);
	// fix_map(data);
	data->player->rotation_angle = M_PI * 2;
	data->player->rotation_speed = 6 * (M_PI / 180);
	data->player->move_speed = 0.1;
	data->player->rot_speed = 0.1;
	data->player->tab[0] = 0;
	data->player->tab[1] = 0;
	data->player->tab[2] = 0;
	data->player->tab[13] = 0;
	data->player->tab[123] = 0;
	data->player->tab[124] = 0;
	data->rayangle = 0;
}