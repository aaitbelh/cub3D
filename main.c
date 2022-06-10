/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:48:55 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/10 17:07:30 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "include/cub3d.h"
#include <string.h>
char **read_map(char *name)
{
	int		fd;
	char	*buf;
	char	**map;
	int		size;
	char	*line;



	fd = open(name, O_RDONLY);
	if (fd == -1)
		ft_error_exit("can't open map\n");
	map = malloc(sizeof(char *) * (size + 1));
	line = NULL;
	while(1)
	{
		buf = get_next_line(fd);
		if(!buf)
			break;
		line = ft_strjoin_get(line, buf);
		free(buf);
		size++;
	}
	map = ft_split(line, '\n');
	free(line);
	return (map);
}

int	check_map_name(char *str)
{
	char	*new;
	int		i;
	int		fd;

	i = 0;
	while(str[i] && str[i] != '.')
		i++;
	new = malloc(sizeof(char) * (i + 1));
	fd = open(str, O_RDONLY);
	if(!new)
		return (1);
	new = ft_strchr(str, '.');
	if(!new || ft_strcmp(new, ".cub") || fd == -1)
		return (1);
	return (0);

}

void	count_w_h(t_game *game, int i)
{
	int	hight;
	int	width;

	
	hight = 0;
	width = 0;
	while (game->map[i][width])
		width++;
	while (game->map[hight])
		hight++;
	game->ply_map->width = width;
	game->ply_map->hight = hight;
	
}

void	draw_line(t_game *game, t_line *line, int len)
{
	float	x;
	float	y;
	float	l;
	float	step = 0.1;

	line->offset_x  = game->player->x *  20;
	line->offset_y  = game->player->y *  20;
	l = 0.0;
	while (l < len)
	{
		x = cos(game->player->rotation_angle) * l;
		y = sin(game->player->rotation_angle) * l;
		mlx_pixel_put(game->mlx,game->win, line->offset_x + x, line->offset_y + y, 0xFF0000);
		l += step;
	}
}


void draw_cyrcle(t_game *game , t_line *line)
{
	double	l;
	float	y;
	float	x;
	float	step;
	
	line->offset_x  = game->player->x *  20;
	line->offset_y  = game->player->y *  20;
	l = 0.0;
	step = 0.0;
	while (l < M_PI * 2)
	{
		step = 0;
		while (step < 5)
		{
			x = cos(l) * step;
			y = sin(l) * step;
			mlx_pixel_put(game->mlx, game->win, game->player->x * 20 + x, game->player->y * 20 + y, 0xFF0000);
			step += 0.2;
		}
		l += 0.01;
	}
}
void draw_square(t_game *data, float x, float y, int color)
{
	float	i;
	float	j;

	j = 0;
	while(j < 20)
	{
		i = 0;
		while(i < 20)
		{
			mlx_pixel_put(data->mlx, data->win, x + i, y + j, color);
			i += 1.5;
		}
		j += 1.5;
	}
}
void	draw_it(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	int ret;
	while(data->map[i])
	{
		j = 0;
		while(data->map[i][j])
		{
			if(data->map[i][j] == '1')
				draw_square(data, j * 20, i * 20, 0xFFFFFF);
			if(data->map[i][j] == '0')
				draw_square(data, j * 20, i * 20, 0);
			j++;
		}
		i++;
	}
}

float	normalizeAngle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle = 2 * M_PI + angle;
	return (angle);
}

void	rayFacing(float angle, t_game *game, int i)
{
	if (angle > 0 && angle < M_PI)
	{
		game->rays[i].isRayFacingDown = 1;
		game->rays[i].isRayFacingUp = 0;
	}
	else
	{
		game->rays[i].isRayFacingDown = 0;
		game->rays[i].isRayFacingUp = 1;
	}
	if (angle < 0.5 * M_PI || angle > 1.5 * M_PI)
	{
		game->rays[i].isRayFacingRight = 1;
		game->rays[i].isRayFacingLeft = 0;
	}
	else
	{
		game->rays[i].isRayFacingRight = 0;
		game->rays[i].isRayFacingLeft = 1;
	}
}

int	mapHasWallAt(t_game *game, float x, float y)
{
	int X;
	int Y;

	X = floor(x / 20);
	Y = floor(y / 20);
	printf("%d %d %c\n", Y,X,game->map[Y][X]);
	if (game->map[Y][X] == '1')
		return (1);
	return (0);
}

void	foundHitH(t_game *game, float x, float y, int i)
{
	float	xToCheck;
	float	yToCheck;

	game->rays[i].wasHitHorz = 0;
	while (x >= 0 && x <= 1900 && y >= 0 && y <= 900)
	{
		xToCheck = x;
		yToCheck = y;
		if (game->rays[i].isRayFacingUp)
		 	yToCheck -= 1;
		if (mapHasWallAt(game, xToCheck, yToCheck))
		{
			game->rays[i].horzHitX = x;
			game->rays[i].horzHitY = y;
			game->rays[i].wasHitVert = 1;
			break ;
		}
		else
		{
			x += game->rays[i].xstep;
			y += game->rays[i].ystep;
		}
	}
}

void	foundHorzWallHit(float rayAngle, t_game *game, int i)
{
	float	xintercept;
	float	yintercept;

	rayFacing(rayAngle, game, i);
	yintercept = floor(game->player->y) * 20;
	if (game->rays[i].isRayFacingDown)
		yintercept += 20;
	xintercept = game->player->x * 20 + (yintercept - (game->player->y * 20)) / tan(rayAngle);
	game->rays[i].ystep = 20;
	if (game->rays[i].isRayFacingUp)
		game->rays[i].ystep *= -1;
	game->rays[i].xstep = 20 / tan(rayAngle);
	if (game->rays[i].isRayFacingLeft && game->rays[i].xstep > 0)
		game->rays[i].xstep *= -1;
	if (game->rays[i].isRayFacingRight && game->rays[i].xstep < 0)
		game->rays[i].xstep *= -1;
	foundHitH(game, xintercept, yintercept, i);
}

void	foundHitV(t_game *game, float x, float y, int i)
{
	float	xToCheck;
	float	yToCheck;

	game->rays[i].wasHitVert = 0;
	while (x >= 0 && x <= 1900 && y >= 0 && y <= 900)
	{
		xToCheck = x;
		yToCheck = y;
		if (game->rays[i].isRayFacingUp)
			yToCheck -= 1;
		if (mapHasWallAt(game, xToCheck, yToCheck))
		{
			printf("oui\n");
			game->rays[i].vertHitX = x;
			game->rays[i].vertHitY = y;
			game->rays[i].wasHitVert = 1;
			break ;
		}
		else
		{
			x += game->rays[i].xstep;
			y += game->rays[i].ystep;
		}
	}
}

void	foundVertWallHit(float rayAngle, t_game *game, int i)
{
	float	xintercept;
	float	yintercept;

	xintercept = floor(game->player->x / 20) * 20;
	if (game->rays[i].isRayFacingRight)
		xintercept += 20;
	yintercept = game->player->x + (xintercept - game->player->x) * tan(rayAngle);
	game->rays[i].xstep = 20;
	if (game->rays[i].isRayFacingLeft)
		game->rays[i].xstep *= -1;
	game->rays[i].ystep = 20 * tan(rayAngle);
	if (game->rays[i].isRayFacingUp && game->rays[i].ystep > 0)
		game->rays[i].ystep *= -1;
	if (game->rays[i].isRayFacingDown && game->rays[i].ystep < 0)
		game->rays[i].ystep *= -1;
	foundHitV(game, xintercept, yintercept, i);
}

float	distance(x1, x2, y1, y2)
{
	return (sqrt((x2 + x1) * (x2 + x1) + (y2 - y1) * (y2 - y1)));
}

void	foundClosestHit(t_game *game, int i)
{
	float	horzHitDistance;
	float	vertHitDistance;


	horzHitDistance = INT_MAX;
	vertHitDistance = INT_MAX;
	printf("%d   %d\n", game->rays[i].wasHitHorz, game->rays[i].wasHitVert);
	if (game->rays[i].wasHitHorz)
		horzHitDistance = distance(game->player->x, game->rays[i].horzHitX, game->player->y, game->rays[i].horzHitY);
	if (game->rays[i].wasHitVert)
		vertHitDistance = distance(game->player->x, game->rays[i].vertHitX, game->player->y, game->rays[i].vertHitY);
	if (horzHitDistance < vertHitDistance)
	{
		game->rays[i].HitX = game->rays[i].horzHitX;
		game->rays[i].HitY = game->rays[i].horzHitY;
		game->rays[i].HitDistance = horzHitDistance;	
	}
	else
	{
		game->rays[i].HitX = game->rays[i].vertHitX;
		game->rays[i].HitY = game->rays[i].vertHitY;
		game->rays[i].HitDistance = vertHitDistance;	
	}
}

void	castOneRay(t_game *game, int i)
{
	float	rayAngle;
	
	game->rays[i].rayAngle = normalizeAngle(game->rays[i].rayAngle);
	rayAngle = game->rays[i].rayAngle;
	foundHorzWallHit(rayAngle, game, i);
	foundVertWallHit(rayAngle, game, i);
	foundClosestHit(game, i);
}

void	castAllRays(t_game *game)
{
	float	rayAngle;
	int		i;

	rayAngle = game->player->rotation_angle - (FOV_ANGLE / 2);
	i = 0;
	while (i < 1)
	{
		game->rays[i].rayAngle = rayAngle;
		castOneRay(game, i);
		rayAngle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}

void	drawRay(t_game *game, int i)
{
	float	x;
	float	y;
	float	l;
	int		offset_x;
	int		offset_y;

	offset_x  = game->player->x *  20;
	offset_y  = game->player->y *  20;
	l = 0.0;
	while (l < game->rays[i].HitDistance)
	{
		x = cos(game->rays[i].rayAngle) * l;
		y = sin(game->rays[i].rayAngle) * l;
		mlx_pixel_put(game->mlx,game->win, offset_x + x, offset_y + y, 0xFF0000);
		l += 0.1;
	}
}

void	renderRays(t_game *game)
{
	int	i;

	i = 0;
	while (i < 1)
	{
		drawRay(game, i);
		i++;
	}
}

void update(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_it(game);
	draw_cyrcle(game, game->line);
	draw_line(game, game->line, 20);
	castAllRays(game);
	renderRays(game);
	if(game->player->rotation_angle >= 4 * M_PI || game->player->rotation_angle <= 0.000001)
		game->player->rotation_angle = 2 * M_PI;
}
int keys(int key, t_game *game)
{
	game->player->tab[key] = 1;
	return (1);
}
int keys2(int key, t_game *game)
{
	game->player->tab[key] = 0;
	return (1);
}


int render(t_game *game)
{
	if(game->player->tab[13])
		move_up(game);
	if(game->player->tab[1])
		move_down(game);
	if(game->player->tab[124])
		game->player->rotation_angle += game->player->rotation_speed;
	if(game->player->tab[123])
		game->player->rotation_angle -= game->player->rotation_speed;
	if(game->player->tab[2])
		move_right(game);
	if(game->player->tab[0])
		move_left(game);
	update(game);
	return (1);
}

void	check_map(char **str, t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if(str[i][j] == '0')
			{
				k = j;
				while (str[i][k] && str[i][k] != '1')
					k++;
				if (!str[i][k] && i != game->ply_map->hight - 1)
					ft_error_exit("error1\n");
				k = j;
				while (k > 0 && str[i][k] != '1')
					k--;
				if((k == 0 &&  i != 0 && i != game->ply_map->hight - 1) && str[i][k] != '1')
					ft_error_exit("error2\n");
				k = i;
				while(k < game->ply_map->hight - 1&& str[k][j] != '1')
					k++;
				if((k == game->ply_map->hight - 1 && i != game->ply_map->hight - 1) &&  str[k][j] != '1')
					ft_error_exit("error3\n"); 
				k = i;
				while((k > 0 && k != game->ply_map->hight - 1) &&  str[k][j] != '1')
					k--;
				if((k == 0 && i != 0 && i != game->ply_map->hight - 1) && str[k][j] != '1')
				{
					printf("%d %d '%c'\n", k, j, str[k][j]);
					ft_error_exit("error4\n");
				}
			}
			j++;
		}	
		i++;
	}
}

int main(int ac, char **av ,char **env)
{

	if(ac > 2 || ac < 2)
		ft_error_exit("not enough argument\n");
	t_game *data;
	data = malloc(sizeof(t_game));
	data->ply_map = malloc(sizeof(t_maps));
	data->player = malloc(sizeof(t_player));
	data->line = malloc(sizeof(t_line));
	data->map_name  = ft_strdup(av[ac - 1]);
	data->rays = malloc(sizeof(t_ray) * NUM_RAYS);
	if(check_map_name(data->map_name))
		ft_error_exit("Wrong Map!\n");
	data->map = read_map(data->map_name);
	count_w_h(data, 0);
	check_map(data->map, data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1900 ,900, "prototype");
	data->player->x = 5;
	data->player->y = 5;
	data->player->rotation_angle = 2 * M_PI;
	data->player->rotation_speed = 15 * (M_PI / 180);
	data->player->move_speed = 0.2;
	for(int i  = 0; i <= 2 ; i++)
		data->player->tab[i] = 0;
	data->player->tab[13] = 0;
	mlx_hook(data->win, 02, 1L, keys, data);
	mlx_hook(data->win, 03, 2L, keys2, data);
	mlx_loop_hook(data->mlx, render, data);
	draw_it(data);
	mlx_loop(data->mlx);
}