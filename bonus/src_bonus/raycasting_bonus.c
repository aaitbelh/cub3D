/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:40:30 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/07/31 09:40:41 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

void	get_tex(t_game *game, t_ray *r)
{
	if (r->side == 0)
		game->wallx = game->player->y + r->perpwalldist * r->raydiry;
	else
		game->wallx = game->player->x + r->perpwalldist * r->raydirx;
	game->tex_x = (game->wallx - (int)game->wallx) * 64;
	game->step = 1.0 * 64 / r->lineheight;
	game->tex_pos = ((r->drawstart - 900 / 2)
			+ (r->lineheight / 2)) * game->step;
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
	while (++i < 1800)
	{
		r->camerax = 2 * i / (double)1800 - 1.0;
		r->raydirx = game->player->dirx + r->planex * r->camerax;
		r->raydiry = game->player->diry + r->planey * r->camerax;
		r->mapx = (int)game->player->x;
		r->mapy = (int)game->player->y;
		get_side_dist(game, r);
		get_hit_distance(game, r);
		get_line_height(r);
		get_tex(game, r);
		fill_image(game, i, r->drawstart, r->drawend);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->t.img, 0, 0);
	draw_minimap(game);
	mlx_destroy_image(game->mlx, game->t.img);
}
