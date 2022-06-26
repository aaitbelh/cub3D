/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializeAll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 08:39:56 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/26 20:45:35 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	GetDirectionOfPlayer(t_game *game)
{
	if (game->player->rederaction == 'W')
	{
		game->player->dirX = -1.0;
		game->player->dirY = 0.0;
		game->ray->planeX = 0.0;
		game->ray->planeY = 0.66;
	}
	if (game->player->rederaction == 'E')
	{
		game->player->dirX = 1.0;
		game->player->dirY = 0.0;
		game->ray->planeX = 0.0;
		game->ray->planeY = -0.66;
	}
	if(game->player->rederaction == 'N')
	{
		game->player->dirX = 0.0;
		game->player->dirY = -1.0;
		game->ray->planeX = 0.66;
		game->ray->planeY = 0.0;
	}
	if(game->player->rederaction == 'S')
	{
		game->player->dirX = 0.0;
		game->player->dirY = 1.0;
		game->ray->planeX = -0.66;
		game->ray->planeY = 0.0;
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
	game->ply_map->c = 0;
	game->ply_map->no = 0;
	game->ply_map->se = 0;
	game->ply_map->we = 0;
	game->ply_map->ea = 0;
	game->ply_map->f = 0;
	// game->player->dirX = -1.0;
	// game->player->dirY = 0.0;
	// game->ray->planeX = 0.0;
	// game->ray->planeY = 0.66;
}

void initializeData(int ac, char **av, t_game *data)
{
	(void)ac;
	data->ply_map = malloc(sizeof(t_maps));
	data->player = malloc(sizeof(t_player));
	data->line = malloc(sizeof(t_line));
	data->ray = malloc(sizeof(t_ray));
	if(check_map_name(av[1]))
		ft_error_exit("Wrong Map!\n");
	data->map = read_map(av[1]);
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