/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseMap2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:11:31 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/27 11:26:52 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	getplayerposition(t_game *game)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player->x = j;
				game->player->y = i;
				game->player->rederaction = game->map[i][j];
				game->map[i][j] = '0';
				count++;
			}
			else if (game->map[i][j] != '0' && game->map[i][j] != '1')
				ft_error_exit("invalid charterer in map");
			j++;
		}
		i++;
	}
	if (count != 1)
		ft_error_exit("player position not found or too much\n");
}

void	getcolor(t_game *game, char *str, char *type)
{
	int		i;
	char	**colors;
	int		rgb[3];

	i = 0;
	colors = ft_split(str, ',');
	if (!ft_strcmp(type, "F"))
	{
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
		twodfree(colors);
	}
	if (!ft_strcmp(type, "C"))
	{
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
		twodfree(colors);
	}
}

void	whattypeis(t_game *game, char *str)
{
	void	*ptr;
	int		lol;
	char	*type;

	if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
		type = ft_strdup("NO");
	if (str[0] == 'S' && str[1] == 'E' && str[2] == ' ')
		type = ft_strdup("SE");
	if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
		type = ft_strdup("WE");
	if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
		type = ft_strdup("EA");
	if (str[0] == 'F' && str[1] == ' ')
		type = ft_strdup("F");
	if (str[0] == 'C' && str[1] == ' ')
		type = ft_strdup("C");
	if (ft_strlen(str) > ft_strlen(type) + 1)
		str += ft_strlen(type);
	else
		ft_error_exit("error in map\n");
	while (*str && *str == ' ')
		str++;
	if (!ft_strcmp(type, "NO") || !ft_strcmp(type, "SE")
		|| !ft_strcmp(type, "WE") || !ft_strcmp(type, "EA"))
	{
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
	else if (!ft_strcmp(type, "F") || !ft_strcmp(type, "C"))
		getcolor(game, str, type);
	free(type);
}

char	**getnewmap(char **map)
{
	int		i;
	char	**new;

	i = 6;
	while (map[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		ft_error_exit("error in malloc\n");
	i = 6;
	while (map[i])
	{
		new[i - 6] = ft_strdup(map[i]);
		i++;
	}
	new[i - 6] = NULL;
	twodfree(map);
	return (new);
}

void	checkelement(t_game *game)
{
	int		i;
	char	*str;

	i = 0;
	while (game->map[i] && i < 6)
	{
		str = ft_strtrim(game->map[i], ' ');
		whattypeis(game, str);
		free(str);
		i++;
	}
	if (game->ply_map->no != 1 || game->ply_map->se != 1
		|| game->ply_map->we != 1
		|| game->ply_map->ea != 1 || game->ply_map->f != 1
		|| game->ply_map->c != 1)
		ft_error_exit("Too much or missed some element\n");
	game->map = getnewmap(game->map);
}
