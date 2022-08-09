/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseMap2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:11:31 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/08/08 16:29:04 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
			getplayerchars(game, i, j, &count);
			j++;
		}
		i++;
	}
	if (count != 1)
		ft_error_exit("player position not found or too much\n");
}

void	getcolor(t_game *game, char *str, char *type)
{
	char	**colors;
	int		len;
	int		i;

	len = 0;
	i = -1;
	if (!ft_strcmp(type, "F") || !ft_strcmp(type, "C"))
	{
		while (str[++i])
			if (str[i] == ',')
				len++;
		if (len != 2)
			ft_error_exit("Celling or floor color parametere problem\n");
		colors = ft_split(str, ',');
		if (!ft_strcmp(type, "F"))
		{
			getfloorcolor(colors, game);
			twodfree(colors);
		}
		if (!ft_strcmp(type, "C"))
		{
			getceillingcolor(colors, game);
			twodfree(colors);
		}
	}
}

void	whattypeis(t_game *game, char *str)
{
	int		lol;
	char	*type;

	type = gettype(str);
	lol = 0;
	if (ft_strlen(str) > ft_strlen(type) + 1)
		str += ft_strlen(type);
	while (*str && *str == ' ')
		str++;
	if (!ft_strcmp(type, "NO") || !ft_strcmp(type, "SE")
		|| !ft_strcmp(type, "WE") || !ft_strcmp(type, "EA"))
	{
		getimgpath(game, type, str, lol);
	}
	else if (!ft_strcmp(type, "F") || !ft_strcmp(type, "C"))
		getcolor(game, str, type);
	free(type);
}

char	**getnewmap(char **map)
{
	int		i;
	char	**new;
	int		tmp;

	i = 6;
	while (map[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		ft_error_exit("error in malloc\n");
	tmp = get_lenght(map);
	fill_map(map, new, tmp);
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
