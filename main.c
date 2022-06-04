/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:48:55 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/03 17:32:13 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "include/cub3d.h"
#include <string.h>
char **read_map(char *name)
{
	int		fd;
	char	*buf;
	char	**map;
	int		size;
	char	*line;



	fd = open(name, O_RDONLY);
	if (fd == -1)
		ft_error_exit("can't open map\n");
	map = malloc(sizeof(char *) * (size + 1));
	line = NULL;
	while(1)
	{
		buf = get_next_line(fd);
		if(!buf)
			break;
		line = ft_strjoin_get(line, buf);
		free(buf);
		size++;
	}
	map = ft_split(line, '\n');
	free(line);
	return (map);
}

int	check_map_name(char *str)
{
	char	*new;
	int		i;
	int		fd;

	i = 0;
	while(str[i] && str[i] != '.')
		i++;
	new = malloc(sizeof(char) * (i + 1));
	fd = open(str, O_RDONLY);
	if(!new)
		return (1);
	new = ft_strchr(str, '.');
	if(!new || ft_strcmp(new, ".cub") || fd == -1)
		return (1);
	return (0);

}

void	count_w_h(t_maps *map, char **map_table)
{
	int	i;
	int	j;
	
	i = 0;
	j = i;
	while(map_table[i])
		i++;
	while(map_table[0][j])
		j++;
	map->width = j;
	map->hight = i;
}


void	f(t_game *game, double angle, int offset_x, int offset_y, int len, int color)
{
	float	x;
	float	y;
	float	l;
	float	step = 0.2;
	
	l = 0.0;
	while (l < len)
	{
		x = cos(angle) * l;
		y = sin(angle) * l;
		mlx_pixel_put(game->mlx,game->win, x + offset_x, y + offset_y, color);
		l += step;
	}
}


void draw_cyrcle(t_game *game)
{
	float l = 0;
	while(l < M_PI * 2)
	{
		f(game, l, game->player->x * 32, game->player->y * 32, 5, 0xFF0000);
		l+= 0.01;
	}
}
void	draw_it(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	int ret;
	while(data->map[i])
	{
		j = 0;
		while(data->map[i][j])
		{
			if(data->map[i][j] == '1')
			{
				mlx_put_image_to_window(data->mlx, data->win, data->cube, j * 32,  i * 32);
			}
			j++;
		}
		i++;
	}
	draw_cyrcle(data);
	f(data, data->player->rotation_angle, data->player->x *  32, data->player->y * 32 ,20, 0xFF0000);
}

void update(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	f(game, game->player->rotation_angle, game->player->x *  32, game->player->y * 32 ,20, 0xFF0000);
	draw_cyrcle(game);
	draw_it(game);
}
int keys(int key, t_game *game)
{
	if(key == 126)
		game->player->tab[126]= 1;
	if(key == 124)
		game->player->tab[124] = 1;
	if(key == 125)
		game->player->tab[125] = 1;
	if(key == 123)
		game->player->tab[123] = 1;
	return (1);
}
int keys2(int key, t_game *game)
{
	if(key == 126)
		game->player->tab[126]= 0;
	if(key == 124)
		game->player->tab[124] = 0;
	if(key == 125)
		game->player->tab[125] = 0;
	if(key == 123)
		game->player->tab[123] = 0;
	return (1);
}
int render(t_game *game)
{
	if(game->player->tab[126])
	{
		game->player->move_step = game->player->move_speed *  1;
		game->player->x +=  cos(game->player->rotation_angle) *  game->player->move_step;
		game->player->y += sin(game->player->rotation_angle) *  game->player->move_step;	
	}
	if(game->player->tab[125])
	{
		game->player->move_step = -game->player->move_speed;
		game->player->x +=  cos(game->player->rotation_angle) *  game->player->move_step;
		game->player->y += sin(game->player->rotation_angle) *  game->player->move_step;
	}
	if(game->player->tab[124])
		game->player->rotation_angle += game->player->rotation_speed;
	if(game->player->tab[123])
		game->player->rotation_angle -= game->player->rotation_speed;
	update(game);
	return (1);
}

int main(int ac, char **av ,char **env)
{

	if(ac > 2 || ac < 2)
		ft_error_exit("not enough argument\n");
	t_game *data;
	data = malloc(sizeof(t_game));
	data->ply_map = malloc(sizeof(t_maps));
	data->player = malloc(sizeof(t_player));
	data->map_name  = ft_strdup(av[ac - 1]);
	if(check_map_name(data->map_name))
		ft_error_exit("Wrong Map!\n");
	data->map = read_map(data->map_name);
	data->mlx = mlx_init();
	count_w_h(data->ply_map, data->map);
	int width = 1900;
	int hight = 900;
	data->win = mlx_new_window(data->mlx, 1900 ,900, "prototype");
	int p = 32;
	int l = 32;
	data->cube  = mlx_xpm_file_to_image(data->mlx, "cube.xpm", &p , &p);
	data->cyrcle = mlx_xpm_file_to_image(data->mlx, "cyrcle.xpm", &l , &l);
	data->player->x = data->ply_map->width / 2;
	data->player->y = data->ply_map->hight / 2;
	data->player->rotation_angle = M_PI / 2;
	data->player->rotation_speed = 15 * (M_PI / 180);
	data->player->walkdaraction = 0;
	data->player->turndaraction = 0;
	data->player->move_speed = 0.3;
	mlx_hook(data->win, 02, 1L, keys, data);
	mlx_hook(data->win, 03, 2L, keys2, data);
	mlx_loop_hook(data->mlx, render, data);
	draw_it(data);
	mlx_loop(data->mlx);
}