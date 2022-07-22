/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:49:36 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/07/22 14:48:33 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	int		begin_x;
	int		begin_y;
	int		i;
	int		j;
	int		tmp_x;

	begin_x = (int)game->player->x - 10;
	begin_y = (int)game->player->y - 10;
	i = 0;
	while (i < 200)
	{
		if (i % 10 == 0 && i != 0)
			begin_y++;
		j = 0;
		tmp_x = begin_x;
		while (j < 200)
		{
			if (j % 10 == 0 && j != 0)
				tmp_x++;
			if (begin_y < 0 || begin_y >= game->ply_map->hight
				|| tmp_x < 0 || tmp_x >= game->ply_map->width)
				draw_pixel_in_image(game, i, j, 0x000000);
			else
			{
				if (game->map[begin_y][tmp_x] == '1')
					draw_pixel_in_image(game, i, j, 0xFFFFFF);
				else
					draw_pixel_in_image(game, i, j, 0x000000);
			}
			if (begin_y == (int)game->player->y
				&& tmp_x == (int)game->player->x)
				draw_pixel_in_image(game, i, j, 0xFF0000);
			j++;
		}
		i++;
	}
}
