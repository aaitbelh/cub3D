/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:40:30 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/07/03 10:04:28 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	getcolorfromimg(t_game *game)
{
	t_ray	*r;

	r = game->ray;
	if (r->side == 0 && r->rayDirX < 0)
		game->colorPointer = mlx_get_data_addr(game->ply_map->wtexture, &game->tbits , &game->tsize_line, &game->tendian);
	if (r->side == 0 && r->rayDirX >= 0)
		game->colorPointer = mlx_get_data_addr(game->ply_map->etexture, &game->tbits , &game->tsize_line, &game->tendian);
	if (r->side == 1 && r->rayDirY < 0)
		game->colorPointer = mlx_get_data_addr(game->ply_map->ntexture, &game->tbits , &game->tsize_line, &game->tendian);
	if (r->side == 1 && r->rayDirY >= 0)
		game->colorPointer = mlx_get_data_addr(game->ply_map->stexture, &game->tbits , &game->tsize_line, &game->tendian);
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
	int *color;

	j = -1;
	while (++j < wallStart)
		put_pixel_in_image(game, i, j, game->ply_map->ccolor);
	j = wallStart;
	getcolorfromimg(game);
	while (j < wallEnd)
	{
		game->texY = game->texPos;
		game->texPos += game->step;
		color = (int *)(game->colorPointer + (game->tsize_line * game->texY \
		+ game->texX * (game->tbits / 8)));
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
	if (r->rayDirX == 0)
		r->deltaDistX = 1e30;
	else
		r->deltaDistX = fabs(1 / r->rayDirX);
	if (r->rayDirY == 0)
		r->deltaDistY = 1e30;
	else
		r->deltaDistY = fabs(1 / r->rayDirY);
}

void	get_side_dist(t_game *game, t_ray *r)
{
	get_delta_dist(r);
	if (r->rayDirX < 0)
	{
		r->stepX = -1;
		r->sideDistX = (game->player->x - r->mapX) * r->deltaDistX;
	}
	else
	{
		r->stepX = 1;
		r->sideDistX = (r->mapX + 1.0 - game->player->x) * r->deltaDistX;
	}
	if (r->rayDirY < 0)
	{
		r->stepY = -1;
		r->sideDistY = (game->player->y - r->mapY) * r->deltaDistY;
	}
	else
	{
		r->stepY = 1;
		r->sideDistY = (r->mapY + 1.0 - game->player->y) * r->deltaDistY;
	}
}

void	get_hit_distance(t_game *game, t_ray *r)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (r->sideDistX < r->sideDistY)
		{
			r->sideDistX += r->deltaDistX;
			r->mapX += r->stepX;
			r->side = 0;
		}
		else
		{
			r->sideDistY += r->deltaDistY;
			r->mapY += r->stepY;
			r->side = 1;
		}
		if (game->map[r->mapY][r->mapX] == '1')
			hit = 1;
	}
	if (r->side == 0)
		r->perpWallDist = (r->sideDistX - r->deltaDistX);
	else
		r->perpWallDist = (r->sideDistY - r->deltaDistY);
}

void	get_line_height(t_ray *r)
{
	r->lineHeight = (int)(900 / r->perpWallDist);
	r->drawStart = ((-1 * r->lineHeight) / 2) + 450;
	if (r->drawStart < 0)
		r->drawStart = 0;
	r->drawEnd = (r->lineHeight / 2) + 450;
	if (r->drawEnd >= 900)
		r->drawEnd = 899;
}

void	ray_casting(t_game *game)
{
	int		i;
	int		tmp;
	t_ray	*r;

	r = game->ray;
	game->t.img = mlx_new_image(game->mlx, 1800, 900);
	game->t.p = mlx_get_data_addr(game->t.img, &game->t.bits,
			&game->t.size_line, &tmp);
	i = -1;
	while (++i < 1800)
	{
		r->cameraX = 2 * i / (float)1800 - 1.0;
		r->rayDirX = game->player->dirX + r->planeX * r->cameraX;
		r->rayDirY = game->player->dirY + r->planeY * r->cameraX;
		r->mapX = (int)game->player->x;
		r->mapY = (int)game->player->y;
		get_side_dist(game, r);
		get_hit_distance(game, r);
		get_line_height(r);
		if (r->side == 0)
			game->Wallx = game->player->y + r->perpWallDist * r->rayDirY;
		else
			game->Wallx = game->player->x + r->perpWallDist * r->rayDirX;
		game->texX = (game->Wallx - (int)game->Wallx) * 64;
		game->step =  1.0 * 64 / r->lineHeight;
		game->texPos = ((r->drawStart - 900 / 2) + (r->lineHeight / 2)) * game->step;
		fill_image(game, i, r->drawStart, r->drawEnd); 
	}
	mlx_put_image_to_window(game->mlx, game->win, game->t.img, 0, 0);
	mlx_destroy_image(game->mlx, game->t.img);
}