/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:48:55 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/26 18:41:28 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/include/cub3d.h"



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

int  update(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	ray_casting(game);
	return (1);
}

int KeyReleased(int key, t_game *game)
{
	game->player->tab[key] = 1;
	if (key == 53)
		exit(0);
	return (1);
}
int KeyPressed(int key, t_game *game)
{
	game->player->tab[key] = 0;
	if (key == 53)
		exit(0);
	return (1);
}


int render(t_game *game)
{
	if(game->player->tab[13])
		move_up(game);
	if(game->player->tab[1])
		move_down(game);
	if(game->player->tab[124])
		rotate_right(game);
	if(game->player->tab[123])
		rotate_left(game);
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
	i = 0;
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

void	fix_map(t_game *game)
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

int redCross(int Key)
{
	(void)Key;
	exit(1);
}
int main(int ac, char **av)
{

	if(ac > 2 || ac < 2)
		ft_error_exit("not enough argument\n");
	t_game *data;
	data = malloc(sizeof(t_game));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1800 ,900, "prototype");
	initializeData(ac, av, data);
	mlx_hook(data->win, 02, 1L, KeyReleased, data);
	mlx_hook(data->win, 03, 2L, KeyPressed, data);
	mlx_hook(data->win, 17, 0, redCross, NULL);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
}