/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:47:21 by alaajili          #+#    #+#             */
/*   Updated: 2022/06/19 13:00:46 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

float	normalizeAngle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle = 2 * M_PI + angle;
	return (angle);
}

void	rayFacing(float angle, t_game *game)
{
	if (angle > 0 && angle < M_PI)
	{
		game->rays->isRayFacingDown = 1;
		game->rays->isRayFacingUp = 0;
	}
	else
	{
		game->rays->isRayFacingDown = 0;
		game->rays->isRayFacingUp = 1;
	}
	if (angle < 0.5 * M_PI || angle > 1.5 * M_PI)
	{
		game->rays->isRayFacingRight = 1;
		game->rays->isRayFacingLeft = 0;
	}
	else
	{
		game->rays->isRayFacingRight = 0;
		game->rays->isRayFacingLeft = 1;
	}
}

void	drawRay(t_game *game,float D)
{
	float	x;
	float	y;
	float	l;
	int		offset_x;
	int		offset_y;

	offset_x  = game->player->x *  50;
	offset_y  = game->player->y *  50;
	l = 0;
	while (l < D)
	{
		x = cos(game->rayangle) * l;
		y = sin(game->rayangle) * l;
		mlx_pixel_put(game->mlx,game->win, offset_x + x, offset_y + y, 0xFFFF00);
		l += 0.1;
	}
}

int	mapHasWallAt(t_game *game, float x, float y)
{
	int X;
	int Y;

	X = floor(x / 50);
	Y = floor(y / 50);
	if (game->map[Y][X] == '1')
		return (1);
	return (0);
}

void	horinter(t_game *game)
{
	float Ay,Ax;

	game->rays->wasHitHorz = 0;
	if (game->rays->isRayFacingUp)
	{
		game->rays->ystep = -50;
		Ay = floor(game->player->y) * 50 - 1;
	}
	else
	{
		game->rays->ystep = 50;
		Ay = floor(game->player->y) * 50 + 50;
	}
	Ax = (game->player->x * 50) + ((Ay - (game->player->y * 50)) / tan(game->rayangle));
	game->rays->xstep = 50 / tan(game->rayangle);
	if (game->rays->isRayFacingRight && game->rays->xstep < 0)
		game->rays->xstep *= -1;
	if (game->rays->isRayFacingLeft && game->rays->xstep > 0)
		game->rays->xstep *= -1;
	while(Ay <= game->ply_map->hight * 50 && Ax <= game->ply_map->width * 50 && Ay >= 0 && Ax >= 0)
	{
		if (mapHasWallAt(game,Ax,Ay))
		{
			game->rays->wasHitHorz = 1;
			break ;
		}
		Ay += game->rays->ystep;
		Ax += game->rays->xstep;
	}
	game->rays->hDistance = sqrt((Ax - game->player->x * 50) * (Ax - game->player->x * 50) +
		(Ay - game->player->y * 50) * (Ay - game->player->y * 50));
}

void	verinter(t_game *game)
{
	float Ay,Ax;

	game->rays->wasHitVert = 0;
	if (game->rays->isRayFacingLeft)
	{
		game->rays->xstep = -50;
		Ax = floor(game->player->x) * 50 - 1;
	}
	else
	{
		game->rays->xstep = 50;
		Ax = floor(game->player->x) * 50 + 50;
	}
	Ay = game->player->y * 50 + ((Ax - game->player->x * 50) * tan(game->rayangle));
	game->rays->ystep = 50 * tan(game->rayangle);
	if (game->rays->isRayFacingDown && game->rays->ystep < 0)
		game->rays->ystep *= -1;
	if (game->rays->isRayFacingUp && game->rays->ystep > 0)
		game->rays->ystep *= -1;
	while (Ay <= game->ply_map->hight * 50 && Ax <= game->ply_map->width * 50 && Ay >= 0 && Ax >= 0)
	{
		if (mapHasWallAt(game,Ax,Ay))
		{
			game->rays->wasHitVert = 1;
			break;
		}
		Ay += game->rays->ystep;
		Ax += game->rays->xstep;
	}
	game->rays->vDistance = sqrt((Ax - game->player->x*50) * (Ax - game->player->x*50) +
		(Ay - game->player->y*50) * (Ay - game->player->y*50));
}

float	getSliceHeight(t_game *game, int i)
{
	float	DistanceProjPlane;

	DistanceProjPlane = 450 / tan(M_PI / 6);
	return ((50 / game->rays[i].HitDistance) * DistanceProjPlane);
}

void	put_pixel_in_image(t_game *game, int i, int j, int color)
{
	char	*a;

	a = game->t.p + (j * game->t.size_line + i * (game->t.bits / 8));
	*(unsigned int *)a = color;
}

void	fillImage(t_game *game, int i)
{
	int	j;
	float	wallStart;
	float	wallEnd;

	wallStart = 450 - game->rays[i].sliceHeight / 2;
	wallEnd = 450 + game->rays[i].sliceHeight / 2;
	if (wallStart < 0)
		wallStart = 0;
	j = 0;
	while (j < wallStart)
	{
		put_pixel_in_image(game, i, j, 0x000000);
		j++;
	}
	while (j < wallEnd && j < 900)
	{
		put_pixel_in_image(game, i, j, 0xFF0000);
		j++;
	}
	while (j < 900)
	{
		put_pixel_in_image(game, i, j, 0x000000);
		j++;
	}
}

void	drawWalls(t_game *game)
{
	int	i;
	int	tmp;

	i = -1;
	game->t.img = mlx_new_image(game->mlx, 1800, 900);
	game->t.p = mlx_get_data_addr(game->t.img, &game->t.bits, &game->t.size_line, &tmp);
	while (++i < 1800)
	{
		game->rays[i].sliceHeight = getSliceHeight(game, i);
		fillImage(game, i);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->t.img, 0, 0);
	mlx_destroy_image(game->mlx, game->t.img);
}

float	correctDistance(float D, t_game *game)
{
	return (D * cos(game->rayangle - game->player->rotation_angle));
}

void raycasting(t_game *game)
{
	float	D;
	int		i;

	i = -1;
	game->rayangle = (game->player->rotation_angle - M_PI / 6);
	while (++i < 1800)
	{
		game->rayangle = normalizeAngle(game->rayangle);
		rayFacing(game->rayangle, game);
		horinter(game);
		verinter(game);
		if (game->rays->wasHitHorz && !game->rays->wasHitVert)
			D = game->rays->hDistance;
		if (game->rays->wasHitVert && !game->rays->wasHitHorz)
			D = game->rays->vDistance;
		if (game->rays->wasHitHorz && game->rays->wasHitVert)
		{
			if (game->rays->hDistance < game->rays->vDistance)
				D = game->rays->hDistance;
			else
				D = game->rays->vDistance;
		}
		game->rays[i].HitDistance = D;
		game->rays[i].HitDistance = correctDistance(game->rays[i].HitDistance, game);
		game->rayangle += M_PI / 5400;
	}
	drawWalls(game);
}
