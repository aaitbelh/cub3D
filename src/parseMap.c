/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:54:03 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/22 12:21:08 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
					ft_error_exit("error4\n");
				}
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
	new = malloc(sizeof(char) * (i + 1));
	fd = open(str, O_RDONLY);
	if(!new)
		return (1);
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
	int		size;
	char	*line;


	size = 0;
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