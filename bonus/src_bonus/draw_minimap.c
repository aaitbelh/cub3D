/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:49:36 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/07/18 11:44:24 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	draw_pixel_in_image(t_game *game, int i, int j, int color)
{
	char	*a;

	a = game->t.minip + (j * game->t.minisize_line
			+ i * (game->t.minibits / 8));
	*(unsigned int *)a = color;
}

void	draw_line(t_game *game, t_line *line, int len)
{
	float	x;
	float	y;
	float	l;
	float	step;

	step = 0.1;
	line->offset_x = game->player->x * 10;
	line->offset_y = game->player->y * 10;
	l = 0.0;
	while (l < len)
	{
		x = cos(game->player->rotation_angle) * l;
		y = sin(game->player->rotation_angle) * l;
		draw_pixel_in_image(game, line->offset_x
			+ x, line->offset_y + y, 0xFF0000);
		l += step;
	}
}

void	draw_cyrcle(t_game *game, t_line *line)
{
	double	l;
	float	y;
	float	x;
	float	step;

	line->offset_x = game->player->x * 10;
	line->offset_y = game->player->y * 10;
	l = 0.0;
	step = 0.0;
	while (l < M_PI * 2)
	{
		step = 0;
		while (step < 5)
		{
			x = cos(l) * step;
			y = sin(l) * step;
			draw_pixel_in_image(game, game->player->x * 10 + x,
				game->player->y * 10 + y, 0xFF0000);
			step += 0.2;
		}
		l += 0.2;
	}
}

void	draw_square(t_game *game, float x, float y, int color)
{
	int		i;
	int		j;
	int		size;

	size = 20;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			draw_pixel_in_image(game, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	char	**mini;
	int		i;
	int		a;
	int		b;
	int		j;

	mini = malloc(11 * sizeof(char *));
	i = 0;
	a = (int)game->player->y - 5;
	b = (int)game->player->x - 5;
	while (i < 10)
	{
		b = (int)game->player->x - 5;
		mini[i] = malloc(10 * sizeof(char ) + 1);
		j = 0;
		while (j < 10)
		{
			mini[i][j] = game->map[a][b];
			if (b == (int)game->player->x && a == (int)game->player->y)
				mini[i][j] = 'P';
			b++;
			j++;
		}
		mini[i][j] = 0;
		a++;
		i++;
	}
}
