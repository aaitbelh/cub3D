/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:47:21 by alaajili          #+#    #+#             */
/*   Updated: 2022/06/13 20:37:29 by aaitbelh         ###   ########.fr       */
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
	while(Ay <= 250 && Ax <= 700 && Ay >= 0 && Ax >= 0)
	{
		if (mapHasWallAt(game,Ax,Ay))
		{
			game->rays->wasHitHorz = 1;
			break;
		}
		Ay += game->rays->ystep;
		Ax += game->rays->xstep;
	}
	game->rays->hDistance = sqrt((Ax - game->player->x*50) * (Ax - game->player->x*50) +
		(Ay - game->player->y*50) * (Ay - game->player->y*50));
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
	while(Ay <= 250 && Ax <= 700 && Ay >= 0 && Ax >= 0)
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

void raycasting(t_game *game)
{
	float D;
	float i = 0;
	game->rayangle = (game->player->rotation_angle - M_PI / 6);
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
		drawRay(game, D);

}