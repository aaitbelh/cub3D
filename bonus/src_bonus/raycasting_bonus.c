/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:40:30 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/07/21 14:24:06 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

	a = game->t.p + (j * game->t.size_line
			+ i * (game->t.bits / 8));
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

void	get_hit_distance(t_game *game, t_ray *r)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (r->sidedistx < r->sidedisty)
		{
			r->sidedistx += r->deltadistx;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sidedisty += r->deltadisty;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (game->map[r->mapy][r->mapx] == '1')
			hit = 1;
	}
	if (r->side == 0)
		r->perpwalldist = (r->sidedistx - r->deltadistx);
	else
		r->perpwalldist = (r->sidedisty - r->deltadisty);
}

void	get_line_height(t_ray *r)
{
	r->lineheight = (int)(900 / r->perpwalldist);
	r->drawstart = ((-1 * r->lineheight) / 2) + 450;
	if (r->drawstart < 0)
		r->drawstart = 0;
	r->drawend = (r->lineheight / 2) + 450;
	if (r->drawend >= 900)
		r->drawend = 899;
}

void	ray_casting(t_game *game)
{
	int		i;
	t_ray	*r;
	int		tmp;

	r = game->ray;
	i = -1;
	game->t.img = mlx_new_image(game->mlx, 1800, 900);
	game->t.p = mlx_get_data_addr(game->t.img, &game->t.bits,
			&game->t.size_line, &tmp);
	game->t.miniimg = mlx_new_image(game->mlx, 200, 200);
	game->t.minip = mlx_get_data_addr(game->t.miniimg,
			&game->t.minibits, &game->t.minisize_line, &game->t.miniendian);
	while (++i < 1800)
	{
		r->camerax = 2 * i / (float)1800 - 1.0;
		r->raydirx = game->player->dirx + r->planex * r->camerax;
		r->raydiry = game->player->diry + r->planey * r->camerax;
		r->mapx = (int)game->player->x;
		r->mapy = (int)game->player->y;
		get_side_dist(game, r);
		get_hit_distance(game, r);
		get_line_height(r);
		if (r->side == 0)
			game->wallx = game->player->y + r->perpwalldist * r->raydiry;
		else
			game->wallx = game->player->x + r->perpwalldist * r->raydirx;
		game->tex_x = (game->wallx - (int)game->wallx) * 64;
		game->step = 1.0 * 64 / r->lineheight;
		game->tex_pos = ((r->drawstart - 900 / 2)
				+ (r->lineheight / 2)) * game->step;
		fill_image(game, i, r->drawstart, r->drawend);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->t.img, 0, 0);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->t.miniimg, 0, 0);
	mlx_destroy_image(game->mlx, game->t.img);
	mlx_destroy_image(game->mlx, game->t.miniimg);
}
