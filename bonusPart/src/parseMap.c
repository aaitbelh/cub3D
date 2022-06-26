/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:54:03 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/26 12:59:49 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void	checkFory(t_game *game, int i, int j)
{
	int		h;
	int		k;

	h = 0;
	k = i;
	while(game->map[h])
		h++;
	while(game->map[k][j] != '1' && k > 0)
		k--;
	if(game->map[k][j] != '1' && k == 0)
		ft_error_exit("Error Map is not closed\n");
	k = i;
	while(game->map[k][j] != '1' && k < h - 1)
		k++;
	if(game->map[k][j] != '1' && k == h - 1)
		ft_error_exit("Error Map is not closed\n");
}

void	checkForx(t_game *game, int i, int j)
{
	int		k;
	int		w;

	k = j;
	w = 0;
	while(game->map[i][w])
		w++;
	while(game->map[i][k]  != '1' && k < w)
		k++;
	if(game->map[i][k] != '1' && k >= w)
		ft_error_exit("Error: Map is not closed");
	k = j;
	while(game->map[i][k]  != '1' && k > 0)
		k--;
	if(game->map[i][k] != '1' && k <= 0)
		ft_error_exit("Error: Map is not closed");
}


void	check_map(char **str, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if(str[i][j] == '0')
			{
				checkForx(game, i, j);
				checkFory(game, i, j);
			}
			j++;
		}	
		i++;
	}
}

void	count_w_h(t_game *game)
{
	int	hight;
	int	width;

	hight = 0;
	width = 0;
	while (game->map[hight][width])
		width++;
	while (game->map[hight])
		hight++;
	game->ply_map->width = width;
	game->ply_map->hight = hight;
	
}


int	check_map_name(char *str)
{
	char	*new;
	int		i;
	int		fd;

	i = 0;
	while(str[i] && str[i] != '.')
		i++;
	fd = open(str, O_RDONLY);
	new = ft_strchr(str, '.');
	if(!new || ft_strcmp(new, ".cub") || fd == -1)
		return (1);
	return (0);

}

char	**read_map(char *name)
{
	int		fd;
	char	*buf;
	char	**map;
	char	*line;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		ft_error_exit("can't open map\n");
	line = NULL;
	while(1)
	{
		buf = get_next_line(fd);
		if(!buf)
			break;
		line = ft_strjoin_get(line, buf);
		free(buf);
	}
	map = ft_split(line, '\n');
	free(line);
	return (map);
}