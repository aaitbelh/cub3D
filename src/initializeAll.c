/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializeAll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 08:39:56 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/20 05:06:41 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	count_w_h(data);
	check_map(data->map, data);
	fix_map(data);
	data->player->rotation_angle = M_PI* 2;
	data->player->rotation_speed = 0.05;
	data->player->move_speed = 0.1;
	for(int i  = 0; i <= 2 ; i++)
		data->player->tab[i] = 0;
	data->player->tab[13] = 0;
	data->player->tab[123] = 0;
	data->player->tab[124] = 0;
	data->rayangle = 0;
}