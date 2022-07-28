/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:49:36 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/07/28 15:16:47 by alaajili         ###   ########.fr       */
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

void	fill_minimap(t_game *game, int tmp_x, int begin_y, int i)
{
	int	j;

	j = 0;
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
}

void	draw_minimap(t_game *game)
{
	int		begin_x;
	int		begin_y;
	int		i;
	int		tmp_x;

	game->t.miniimg = mlx_new_image(game->mlx, 200, 200);
	game->t.minip = mlx_get_data_addr(game->t.miniimg,
			&game->t.minibits, &game->t.minisize_line, &game->t.miniendian);
	begin_x = (int)game->player->x - 10;
	begin_y = (int)game->player->y - 10;
	i = 0;
	while (i < 200)
	{
		if (i % 10 == 0 && i != 0)
			begin_y++;
		tmp_x = begin_x;
		fill_minimap(game, tmp_x, begin_y, i);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->t.miniimg, 0, 0);
	mlx_destroy_image(game->mlx, game->t.miniimg);
}
