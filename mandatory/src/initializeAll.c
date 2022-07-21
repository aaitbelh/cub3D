/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializeAll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 08:39:56 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/07/21 14:18:11 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	getdirectionofplayer2(t_game *game)
{
	if (game->player->rederaction == 'N')
	{
		game->player->dirx = 0.0;
		game->player->diry = -1.0;
		game->ray->planex = 0.66;
		game->ray->planey = 0.0;
	}
	if (game->player->rederaction == 'S')
	{
		game->player->dirx = 0.0;
		game->player->diry = 1.0;
		game->ray->planex = -0.66;
		game->ray->planey = 0.0;
	}
}

void	getdirectionofplayer(t_game *game)
{
	if (game->player->rederaction == 'W')
	{
		game->player->dirx = -1.0;
		game->player->diry = 0.0;
		game->ray->planex = 0.0;
		game->ray->planey = 0.66;
	}
	if (game->player->rederaction == 'E')
	{
		game->player->dirx = 1.0;
		game->player->diry = 0.0;
		game->ray->planex = 0.0;
		game->ray->planey = -0.66;
	}
	else
		getdirectionofplayer2(game);
}

void	initializemap(t_game *game)
{
	int	i;

	i = 0;
	while (i <= 2)
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
}

void	initializedata(char **av, t_game *data)
{
	data->ply_map = malloc(sizeof(t_maps));
	data->player = malloc(sizeof(t_player));
	data->line = malloc(sizeof(t_line));
	data->ray = malloc(sizeof(t_ray));
	if (check_map_name(av[1]))
		ft_error_exit("Wrong Map!\n");
	data->map = read_map(av[1]);
	initializemap(data);
	checkelement(data);
	check_map(data->map, data);
	fix_map(data);
	getplayerposition(data);
	getdirectionofplayer(data);
	count_w_h(data);
	data->player->rotation_speed = 0.05;
	data->player->move_speed = 0.1;
	data->rayangle = 0;
}
