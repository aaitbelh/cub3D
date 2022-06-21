/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:54:03 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/21 09:08:25 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_map(char **str, t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = 6;
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
					ft_error_exit("map not surrounded by Walls\n");
				k = j;
				while (k > 0 && str[i][k] != '1')
					k--;
				if((k == 0 &&  i != 0 && i != game->ply_map->hight - 1) && str[i][k] != '1')
					ft_error_exit("map not surrounded by Walls\n");
				k = i;
				while(k < game->ply_map->hight - 1&& str[k][j] != '1')
					k++;
				if(k == game->ply_map->hight - 1 &&  str[k][j] != '1')
					ft_error_exit("map not surrounded by Walls\n");
				k = i;
				while((k > 0 && k != game->ply_map->hight - 1) &&  str[k][j] != '1')
					k--;
				if((k == 0 && i != 0 && i != game->ply_map->hight - 1) && str[k][j] != '1')
					ft_error_exit("map not surrounded by Walls\n");
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


void getPlayerPosition(t_game *game)
{
	int	i;
	int	j;
	int	count;

	i = 6;
	count = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{

				game->player->x = j;
				game->player->y = i;
				game->player->rederction = game->map[i][j];
				game->map[i][j] = '0';
				count++;
			}
			j++;
		}
		i++;
	}
	if(count != 1)
		ft_error_exit("player position too much\n");
}

void getColor(t_game *game, char *str, char *type)
{
	int		i;
	char	**colors;
	int  	rgb[3];

	i = 0;
	colors = ft_split(str, ',');
	if(!ft_strcmp(type, "F"))
	{
		game->ply_map->F++;
		while(colors[i])
		{
			if(i < 3)
			{
				rgb[i] = ft_atoi(colors[i]);
				if(rgb[i] > 255 || rgb[i] < 0)
					ft_error_exit("error in floor color\n");
			}
			else
				ft_error_exit("error in floor color N of elements\n");
			i++;
		}
		game->ply_map->Fcolor = ft_rgb_to_hex(rgb[0], rgb[1], rgb[2]);
		TwoDfree(colors);
	}
	if(!ft_strcmp(type, "C"))
	{
		game->ply_map->C++;
		while(colors[i])
		{
			if(i < 3)
			{
				rgb[i] = ft_atoi(colors[i]);
				if(rgb[i] > 255 || rgb[i] < 0)
					ft_error_exit("error in celing color\n");
			}
			else
				ft_error_exit("error in celing color N of elements\n");
			i++;
		}
		game->ply_map->Ccolor = ft_rgb_to_hex(rgb[0], rgb[1], rgb[2]);
		TwoDfree(colors);
	}
}

// void whatTypeis(t_game *game, char *str)
// {
// 	void	*ptr;
// 	int		LOL;
// 	char	*type;
	
// 	if(str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
// 		type = ft_strdup("NO");
// 	if(str[0] == 'S' && str[1] == 'E' && str[2] == ' ')
// 		type = ft_strdup("SE");
// 	if(str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
// 		type = ft_strdup("WE");
// 	if(str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
// 		type = ft_strdup("EA");
// 	if(str[0] == 'F' && str[1] == ' ')
// 		type = ft_strdup("F");
// 	if(str[0] == 'C' && str[1] == ' ')
// 		type = ft_strdup("C");
// 	if(ft_strlen(str) > ft_strlen(type) + 1)
// 		str += ft_strlen(type);
// 	else
// 		ft_error_exit("error in map\n");
// 	while(*str && *str == ' ')
// 		str++;
// 	if(!ft_strcmp(type, "NO") || !ft_strcmp(type, "SE") || !ft_strcmp(type, "WE") || !ft_strcmp(type, "EA"))
// 	{
// 		ptr = mlx_png_file_to_image(game->mlx, str, &LOL, &LOL);
// 		if(!ptr)
// 			ft_error_exit("error : texture path is invalid\n");
// 		if(!ft_strcmp(type, "NO"))
// 		{
// 			game->ply_map->Ntexture = ptr;
// 			game->ply_map->NO++;
// 		}
// 		if(!ft_strcmp(type, "SE"))
// 		{
// 			game->ply_map->Stexture = ptr;
// 			game->ply_map->SE++;
// 		}
// 		if(!ft_strcmp(type, "WE"))
// 		{
// 			game->ply_map->Wtexture = ptr;
// 			game->ply_map->WE++;
// 		}
// 		if(!ft_strcmp(type, "EA"))
// 		{
// 			game->ply_map->Etexture = ptr;
// 			game->ply_map->EA++;
// 		}
// 	}
// 	else if(!ft_strcmp(type, "F") || !ft_strcmp(type, "C"))
// 		getColor(game, str, type);
// 	free(type);
	
// }

// void checkElement(t_game *game)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	while(game->map[i] &&  i < 6)
// 	{
// 		str = ft_strtrim(game->map[i], ' ');
// 		whatTypeis(game, str);
// 		i++;
// 	}
// 	if(game->ply_map->NO != 1 || game->ply_map->SE != 1 || game->ply_map->WE != 1 || game->ply_map->EA != 1 || game->ply_map->F != 1 || game->ply_map->C != 1)
// 		ft_error_exit("Too much or missed some element\n");
// 	getPlayerPosition(game);
// }

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