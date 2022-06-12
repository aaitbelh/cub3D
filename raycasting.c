/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:47:21 by alaajili          #+#    #+#             */
/*   Updated: 2022/06/12 18:08:30 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

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

	offset_x  = game->player->x *  20;
	offset_y  = game->player->y *  20;
	l = 0;
	while (l < D)
	{
		x = cos(game->player->rotation_angle) * l;
		y = sin(game->player->rotation_angle) * l;
		mlx_pixel_put(game->mlx,game->win, offset_x + x, offset_y + y, 0xFFFF00);
		l += 0.1;
	}
}

int	mapHasWallAt(t_game *game, float x, float y)
{
	int X;
	int Y;

	X = floor(x / 20);
	Y = floor(y / 20);
	//printf("y == %d || x == %d\n",Y,X);
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
		game->rays->ystep = -20;
		Ay = floor(game->player->y) * 20 - 1;
	}
	else
	{
		game->rays->ystep = 20;
		Ay = floor(game->player->y) * 20 + 20;
	}
	Ax = (game->player->x * 20) + ((game->player->y * 20) - Ay) / tan(game->player->rotation_angle);
	game->rays->xstep = 20 / tan(game->player->rotation_angle);
	while(Ay <= 100 && Ax <= 280 && Ay >= 0 && Ax >= 0)
	{
		if (mapHasWallAt(game,Ax,Ay))
		{
			game->rays->wasHitHorz = 1;
			break;
		}
		Ay += game->rays->ystep;
		Ax += game->rays->xstep;
	}
	game->rays->hDistance = sqrt((Ax - game->player->x*20) * (Ax - game->player->x*20) +
		(Ay - game->player->y*20) * (Ay - game->player->y*20));
	//printf("h_distance = %f\n",D);
}

void	verinter(t_game *game)
{
	float Ay,Ax;

	game->rays->wasHitVert = 0;
	if (game->rays->isRayFacingLeft)
	{
		game->rays->xstep = -20;
		Ax = floor(game->player->y) * 20 - 1;
	}
	else
	{
		game->rays->xstep = 20;
		Ax = floor(game->player->y) * 20 + 20;
	}
	Ay = game->player->y * 20 + (game->player->x * 20 - Ax) * tan(game->player->rotation_angle);
	game->rays->ystep = 20 * tan(game->player->rotation_angle);
	while(Ay <= 100 && Ax <= 280 && Ay >= 0 && Ax >= 0)
	{
		if (mapHasWallAt(game,Ax,Ay))
		{
			game->rays->wasHitVert = 1;
			break;
		}
		Ay += game->rays->ystep;
		Ax += game->rays->xstep;
	}
	game->rays->vDistance = sqrt((Ax - game->player->x*20) * (Ax - game->player->x*20) +
		(Ay - game->player->y*20) * (Ay - game->player->y*20));
}

void raycasting(t_game *game)
{
	float D;

	rayFacing(game->player->rotation_angle, game);
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
	drawRay(game, D);
}