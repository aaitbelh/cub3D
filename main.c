/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:48:55 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/15 02:32:18 by alaajili         ###   ########.fr       */
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


	size = 0;
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

void	count_w_h(t_game *game)
{
	int	hight;
	int	width;

	hight = 0;
	width = 0;
	while (game->map[hight][width])
		width++;
	while (game->map[hight])
		hight++;
	game->ply_map->width = width;
	game->ply_map->hight = hight;
	
}

void	draw_line(t_game *game, t_line *line, int len)
{
	float	x;
	float	y;
	float	l;
	float	step = 0.1;

	line->offset_x  = game->player->x *  50;
	line->offset_y  = game->player->y *  50;
	l = 0.0;
	while (l < len)
	{
		x = cos(game->player->rotation_angle) * l;
		y = sin(game->player->rotation_angle) * l;
		mlx_pixel_put(game->mlx,game->win, line->offset_x + x, line->offset_y + y, 0xFF0000);
		l += step;
	}
}


void draw_cyrcle(t_game *game , t_line *line)
{
	double	l;
	float	y;
	float	x;
	float	step;
	
	line->offset_x  = game->player->x *  50;
	line->offset_y  = game->player->y *  50;
	l = 0.0;
	step = 0.0;
	while (l < M_PI * 2)
	{
		step = 0;
		while (step < 5)
		{
			x = cos(l) * step;
			y = sin(l) * step;
			mlx_pixel_put(game->mlx, game->win, game->player->x * 50 + x, game->player->y * 50 + y, 0xFF0000);
			step += 0.2;
		}
		l += 0.01;
	}
}
void draw_square(t_game *data, float x, float y, int color)
{
	float	i;
	float	j;

	j = 0;
	while(j < 50)
	{
		i = 0;
		while(i < 50)
		{
			mlx_pixel_put(data->mlx, data->win, x + i, y + j, color);
			i += 1.5;
		}
		j += 1.5;
	}
}
void	draw_it(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	while(data->map[i])
	{
		j = 0;
		while(data->map[i][j])
		{
			if(data->map[i][j] == '1')
				draw_square(data, j * 50, i * 50, 0xFFFFFF);
			if(data->map[i][j] == '0')
				draw_square(data, j * 50, i * 50, 0);
			j++;
		}
		i++;
	}
}



void update(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_it(game);
	draw_cyrcle(game, game->line);
	draw_line(game, game->line, 50);
	raycasting(game);
	if(game->player->rotation_angle >= 4 * M_PI || game->player->rotation_angle <= 0.000001)
		game->player->rotation_angle = 2 * M_PI;
}

int keys(int key, t_game *game)
{
	game->player->tab[key] = 1;
	return (1);
}
int keys2(int key, t_game *game)
{
	game->player->tab[key] = 0;
	return (1);
}


int render(t_game *game)
{
	if(game->player->tab[13])
		move_up(game);
	if(game->player->tab[1])
		move_down(game);
	if(game->player->tab[124])
		game->player->rotation_angle += game->player->rotation_speed;
	if(game->player->tab[123])
		game->player->rotation_angle -= game->player->rotation_speed;
	if(game->player->tab[2])
		move_right(game);
	if(game->player->tab[0])
		move_left(game);
	update(game);
	return (1);
}


char	**makeMapRect(t_game *game)
{
	int	i;
	int	tmp;
	int	j;
	char **new;

	i = 0;
	while(game->map[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	tmp = 0;
	tmp = ft_strlen(game->map[0]);
	i = 1;
	while(game->map[i])
	{
		if(tmp < ft_strlen(game->map[i]))
			tmp = ft_strlen(game->map[i]);
		i++;		
	}
	if(!new)
		return (NULL);
	i = 0;
	while(game->map[i])
	{
		j = 0;
		new[i] = malloc(sizeof(char) * (tmp + 1));
		while(j < tmp)
		{
			if(j < ft_strlen(game->map[i]))
			{
				new[i][j] = game->map[i][j];
			}
			else
				new[i][j] = '0';
			j++;
		}
		new[i][j] = '\0';
		i++;
	}
	new[i] = NULL;
	TwoDfree(game->map);
	return (new);
} 

void fix_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while(game->map[i])
	{
		j = 0;
		while(game->map[i][j])
		{
			if(game->map[i][j] == ' ')
				game->map[i][j] = '0';
			j++;
		}
		i++;
	}
	game->map = makeMapRect(game);
}

void	check_map(char **str, t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if(str[i][j] == '0')
			{
				k = j;
				while (str[i][k] && str[i][k] != '1')
					k++;
				if (!str[i][k] && i != game->ply_map->hight - 1)
					ft_error_exit("error1\n");
				k = j;
				while (k > 0 && str[i][k] != '1')
					k--;
				if((k == 0 &&  i != 0 && i != game->ply_map->hight - 1) && str[i][k] != '1')
					ft_error_exit("error2\n");
				k = i;
				while(k < game->ply_map->hight - 1&& str[k][j] != '1')
					k++;
				if((k == game->ply_map->hight - 1 && i != game->ply_map->hight - 1) &&  str[k][j] != '1')
					ft_error_exit("error3\n"); 
				k = i;
				while((k > 0 && k != game->ply_map->hight - 1) &&  str[k][j] != '1')
					k--;
				if((k == 0 && i != 0 && i != game->ply_map->hight - 1) && str[k][j] != '1')
				{
					printf("%d %d '%c'\n", k, j, str[k][j]);
					ft_error_exit("error4\n");
				}
			}
			j++;
		}	
		i++;
	}
}

int main(int ac, char **av)
{

	if(ac > 2 || ac < 2)
		ft_error_exit("not enough argument\n");
	t_game *data;
	data = malloc(sizeof(t_game));
	data->ply_map = malloc(sizeof(t_maps));
	data->player = malloc(sizeof(t_player));
	data->line = malloc(sizeof(t_line));
	data->map_name  = ft_strdup(av[ac - 1]);
	data->rays = malloc(sizeof(t_ray) * NUM_RAYS);
	if(check_map_name(data->map_name))
		ft_error_exit("Wrong Map!\n");
	data->map = read_map(data->map_name);
	count_w_h(data);
	check_map(data->map, data);
	fix_map(data);
	for(int i =0 ; data->map[i]; i++)
		printf("%s\n", data->map[i]);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 900 ,900, "prototype");
	data->player->x = 3;
	data->player->y = 2;
	data->player->rotation_angle = M_PI * 2;
	data->player->rotation_speed = 1 * (M_PI / 180);
	data->player->move_speed = 0.2;
	for(int i  = 0; i <= 2 ; i++)
		data->player->tab[i] = 0;
	data->player->tab[13] = 0;
	data->rayangle = 0;
	mlx_hook(data->win, 02, 1L, keys, data);
	mlx_hook(data->win, 03, 2L, keys2, data);
	mlx_loop_hook(data->mlx, render, data);
	draw_it(data);
	mlx_loop(data->mlx);
}