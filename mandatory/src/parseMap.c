/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:54:03 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/08/08 19:13:38 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	checkfory(t_game *game, int y, int x)
{
	if (y == 0 || y == game->highofmap - 1)
		ft_error_exit("error in map not serrundered\n");
	if (game->map[y + 1][x] == ' ')
		ft_error_exit("error in map not serrundered or space founded\n");
	if (game->map[y - 1][x] == ' ')
		ft_error_exit("error in map not serrundered or space founded\n");
}

void	checkforx(t_game *game, int y, int x)
{
	int		lenght;

	lenght = 0;
	while (game->map[y][lenght])
		lenght++;
	if (x == 0 || x == lenght - 1)
		ft_error_exit("error in map not serrundered or space founded\n");
	if (game->map[y][x + 1] == ' ')
		ft_error_exit("error in map not serrundered or space founded\n");
	if (game->map[y][x - 1] == ' ')
		ft_error_exit("error in map not serrundered or space founded\n");
}

void	check_map(char **str, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
		i++;
	game->highofmap = i;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '0')
			{
				checkforx(game, i, j);
				checkfory(game, i, j);
			}
			j++;
		}	
		i++;
	}
}

int	check_map_name(char *str)
{
	char	*new;
	int		i;
	int		fd;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	fd = open(str, O_RDONLY);
	new = ft_strrchr(str, '.');
	if (!new || ft_strcmp(new, ".cub") || fd == -1)
		return (1);
	return (0);
}

char	**read_map(char *name)
{
	int		fd;
	char	*buf;
	char	**map;
	char	*line;
	int		lock;

	lock = 0;
	line = NULL;
	fd = open(name, O_RDONLY);
	if (fd == -1)
		ft_error_exit("can't open map\n");
	while (1)
	{
		buf = get_next_line(fd);
		if (!buf)
			break ;
		line = ft_strjoin_get(line, buf);
		check_newline(buf, &lock);
		free(buf);
	}
	if (!line)
		ft_error_exit("map its empty\n");
	map = ft_split(line, '\n');
	free(line);
	return (map);
}
