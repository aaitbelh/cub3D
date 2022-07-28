/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseMap3_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:35:53 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/07/28 15:18:16 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	getplayerchars(t_game *game, int i, int j, int *count)
{
	if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
	{
		game->player->x = j;
		game->player->y = i;
		game->player->rederaction = game->map[i][j];
		game->map[i][j] = '0';
		(*count)++;
	}
	else if (game->map[i][j] != '0' && game->map[i][j] != '1')
		ft_error_exit("invalid charterer in map");
}

void	getceillingcolor(char **colors, t_game *game)
{
	int	i;
	int	rgb[3];

	i = 0;
	game->ply_map->c++;
	while (colors[i])
	{
		if (i < 3)
		{
			rgb[i] = ft_atoi(colors[i]);
			if (rgb[i] > 255 || rgb[i] < 0)
				ft_error_exit("error in celing color\n");
		}
		else
			ft_error_exit("error in celing color N of elements\n");
		i++;
	}
	game->ply_map->ccolor = ft_rgb_to_hex(rgb[0], rgb[1], rgb[2]);
}

void	getfloorcolor(char **colors, t_game *game)
{
	int	i;
	int	rgb[3];

	i = 0;
	game->ply_map->f++;
	while (colors[i])
	{
		if (i < 3)
		{
			rgb[i] = ft_atoi(colors[i]);
			if (rgb[i] > 255 || rgb[i] < 0)
				ft_error_exit("error in floor color\n");
		}
		else
			ft_error_exit("error in floor color N of elements\n");
		i++;
	}
	game->ply_map->fcolor = ft_rgb_to_hex(rgb[0], rgb[1], rgb[2]);
}

char	*gettype(char *str)
{
	char	*type;

	type = NULL;
	if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
		type = ft_strdup("NO");
	else if (str[0] == 'S' && str[1] == 'E' && str[2] == ' ')
		type = ft_strdup("SE");
	else if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
		type = ft_strdup("WE");
	else if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
		type = ft_strdup("EA");
	else if (str[0] == 'F' && str[1] == ' ')
		type = ft_strdup("F");
	else if (str[0] == 'C' && str[1] == ' ')
		type = ft_strdup("C");
	else
		ft_error_exit("error in map\n");
	return (type);
}

void	getimgpath(t_game *game, char *type, char *str, int lol)
{
	void	*ptr;

	ptr = mlx_png_file_to_image(game->mlx, str, &lol, &lol);
	if (!ptr)
		ft_error_exit("error : texture path is invalid\n");
	if (!ft_strcmp(type, "NO"))
	{
		game->ply_map->ntexture = ptr;
		game->ply_map->no++;
	}
	if (!ft_strcmp(type, "SE"))
	{
		game->ply_map->stexture = ptr;
		game->ply_map->se++;
	}
	if (!ft_strcmp(type, "WE"))
	{
		game->ply_map->wtexture = ptr;
		game->ply_map->we++;
	}
	if (!ft_strcmp(type, "EA"))
	{
		game->ply_map->etexture = ptr;
		game->ply_map->ea++;
	}
}
