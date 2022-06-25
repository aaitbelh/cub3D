/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializeAll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 08:39:56 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/25 11:33:57 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	GetDirectionOfPlayer(t_game *game)
{
	if(game->player->rederaction == 'S')
	{
		game->player->dirX = -game->player->dirX;
		game->ray->planeX = -game->ray->planeX;
		game->ray->planeY = -game->ray->planeY;
	}
} 

void initializeMap(t_game *game)
{
	int	i;

	i = 0;
	while(i <= 2)
	{
		game->player->tab[i] = 0;
		game->player->tab[i + 123] = 0;
		i++;
	}
	game->player->tab[13] = 0;
	game->ply_map->C = 0;
	game->ply_map->NO = 0;
	game->ply_map->SE = 0;
	game->ply_map->WE = 0;
	game->ply_map->EA = 0;
	game->ply_map->F = 0;
	game->player->dirX = -1.0;
	game->player->dirY = 0.0;
	game->ray->planeX = 0.0;
	game->ray->planeY = 0.66;
}

void initializeData(int ac, char **av, t_game *data)
{
	data->ply_map = malloc(sizeof(t_maps));
	data->player = malloc(sizeof(t_player));
	data->line = malloc(sizeof(t_line));
	data->map_name  = ft_strdup(av[ac - 1]);
	data->ray = malloc(sizeof(t_ray));
	if(check_map_name(data->map_name))
		ft_error_exit("Wrong Map!\n");
	data->map = read_map(data->map_name);
	initializeMap(data);
	checkElement(data);
	check_map(data->map, data);
	fix_map(data);
	getPlayerPosition(data);
	GetDirectionOfPlayer(data);
	count_w_h(data);
	data->player->rotation_speed = 0.05;
	data->player->move_speed = 0.1;
	data->rayangle = 0;
}