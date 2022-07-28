/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_tools_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:59:34 by alaajili          #+#    #+#             */
/*   Updated: 2022/07/28 15:00:49 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	get_delta_dist(t_ray *r)
{
	if (r->raydirx == 0)
		r->deltadistx = 1e30;
	else
		r->deltadistx = fabs(1 / r->raydirx);
	if (r->raydiry == 0)
		r->deltadisty = 1e30;
	else
		r->deltadisty = fabs(1 / r->raydiry);
}

void	get_side_dist(t_game *game, t_ray *r)
{
	get_delta_dist(r);
	if (r->raydirx < 0)
	{
		r->stepx = -1;
		r->sidedistx = (game->player->x - r->mapx) * r->deltadistx;
	}
	else
	{
		r->stepx = 1;
		r->sidedistx = (r->mapx + 1.0 - game->player->x) * r->deltadistx;
	}
	if (r->raydiry < 0)
	{
		r->stepy = -1;
		r->sidedisty = (game->player->y - r->mapy) * r->deltadisty;
	}
	else
	{
		r->stepy = 1;
		r->sidedisty = (r->mapy + 1.0 - game->player->y) * r->deltadisty;
	}
}

void	getcolorfromimg(t_game *game)
{
	t_ray	*r;

	r = game->ray;
	if (r->side == 0 && r->raydirx < 0)
		game->color_ptr = mlx_get_data_addr(game->ply_map->wtexture,
				&game->tbits, &game->tsize_line, &game->tendian);
	if (r->side == 0 && r->raydirx >= 0)
		game->color_ptr = mlx_get_data_addr(game->ply_map->etexture,
				&game->tbits, &game->tsize_line, &game->tendian);
	if (r->side == 1 && r->raydiry < 0)
		game->color_ptr = mlx_get_data_addr(game->ply_map->ntexture,
				&game->tbits, &game->tsize_line, &game->tendian);
	if (r->side == 1 && r->raydiry >= 0)
		game->color_ptr = mlx_get_data_addr(game->ply_map->stexture,
				&game->tbits, &game->tsize_line, &game->tendian);
}

void	put_pixel_in_image(t_game *game, int i, int j, int color)
{
	char	*a;

	a = game->t.p + (j * game->t.size_line + i * (game->t.bits / 8));
	*(unsigned int *)a = color;
}

void	fill_image(t_game *game, int i, int wallStart, int wallEnd)
{
	int	j;
	int	*color;

	j = -1;
	while (++j < wallStart)
		put_pixel_in_image(game, i, j, game->ply_map->ccolor);
	j = wallStart;
	getcolorfromimg(game);
	while (j < wallEnd)
	{
		game->tex_y = game->tex_pos;
		game->tex_pos += game->step;
		color = (int *)(game->color_ptr + (game->tsize_line * game->tex_y \
		+ game->tex_x * (game->tbits / 8)));
		put_pixel_in_image(game, i, j, *color);
		j++;
	}
	j = wallEnd;
	if (j < 0)
		return ;
	while (++j < 900)
		put_pixel_in_image(game, i, j, game->ply_map->fcolor);
}
