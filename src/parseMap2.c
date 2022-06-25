/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseMap2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:11:31 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/25 09:10:08 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void getPlayerPosition(t_game *game)
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
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player->x = j;
				game->player->y = i;
				game->player->rederaction = game->map[i][j];
				game->map[i][j] = '0';
				count++;
			}
			else if(game->map[i][j] != '0' && game->map[i][j] != '1')
			{
				ft_error_exit("invalid charterer in map");
			}
			j++;
		}
		i++;
	}
	if(count != 1)
		ft_error_exit("player position not found or too much\n");
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

void whatTypeis(t_game *game, char *str)
{
	void	*ptr = NULL;
	int		LOL;
	char	*type;
	
	if(str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
		type = ft_strdup("NO");
	if(str[0] == 'S' && str[1] == 'E' && str[2] == ' ')
		type = ft_strdup("SE");
	if(str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
		type = ft_strdup("WE");
	if(str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
		type = ft_strdup("EA");
	if(str[0] == 'F' && str[1] == ' ')
		type = ft_strdup("F");
	if(str[0] == 'C' && str[1] == ' ')
		type = ft_strdup("C");
	if(ft_strlen(str) > ft_strlen(type) + 1)
		str += ft_strlen(type);
	else
		ft_error_exit("error in map\n");
	while(*str && *str == ' ')
		str++;
	if(!ft_strcmp(type, "NO") || !ft_strcmp(type, "SE") || !ft_strcmp(type, "WE") || !ft_strcmp(type, "EA"))
	{
		ptr = mlx_png_file_to_image(game->mlx, str, &LOL, &LOL);
		if(!ptr)
			ft_error_exit("error : texture path is invalid\n");
		if(!ft_strcmp(type, "NO"))
		{
			game->ply_map->Ntexture = ptr;
			game->ply_map->NO++;
		}
		if(!ft_strcmp(type, "SE"))
		{
			game->ply_map->Stexture = ptr;
			game->ply_map->SE++;
		}
		if(!ft_strcmp(type, "WE"))
		{
			game->ply_map->Wtexture = ptr;
			game->ply_map->WE++;
		}
		if(!ft_strcmp(type, "EA"))
		{
			game->ply_map->Etexture = ptr;
			game->ply_map->EA++;
		}
	}
	else if(!ft_strcmp(type, "F") || !ft_strcmp(type, "C"))
		getColor(game, str, type);
	
}

void checkElement(t_game *game)
{
	int		i;
	char	*str;
	char	**new;

	i = 0;
	while(game->map[i] &&  i < 6)
	{
		str = ft_strtrim(game->map[i], ' ');
		whatTypeis(game, str);
		free(str);
		i++;
	}
	if(game->ply_map->NO != 1 || game->ply_map->SE != 1 || game->ply_map->WE != 1 || game->ply_map->EA != 1 || game->ply_map->F != 1 || game->ply_map->C != 1)
		ft_error_exit("Too much or missed some element\n");
	i = 0;
	while(game->map[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if(!new)
		ft_error_exit("error in malloc\n");
	i = 5;
	while(game->map[++i])
		new[i - 6] = ft_strdup(game->map[i]);
	new[i - 6] = NULL;
	game->map = new;
}
