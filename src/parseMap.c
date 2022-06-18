/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:54:03 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/18 11:46:12 by aaitbelh         ###   ########.fr       */
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
				if(k == game->ply_map->hight - 1 &&  str[k][j] != '1')
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



void getPlayerPosition(t_game *game)
{
	int	i;
	int	j;
	int	count;

	i = 4;
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
		ft_error_exit("error\n");
}

void checkitValid(t_game *game, int  i)
{
	
	void *ptr;
	int	j;
	int LOL;

	j = 0;
	LOL = 0;
	if(game->map[i][0]  == 'N')
	{
		j = 2;
		while(game->map[i][j] && j == ' ')
			j++;
		j++;
		ptr = mlx_png_file_to_image(game->mlx, &game->map[i][j], &LOL, &LOL);
		if(!ptr)
		{
			printf("%s\n", &game->map[i][j]);
			ft_error_exit("error1\n");
		}

	}
	else if (game->map[i][0] == 'S')
	{
		j = 2;
		while(j == ' ' &&  game->map[i][j])
			j++;
		j++;
		ptr = mlx_png_file_to_image(game->mlx, &game->map[i][j], &LOL, &LOL);
		if(!ptr)
			ft_error_exit("error2\n");
	}
	else if (game->map[i][0] == 'W')
	{
		j = 2;
		while(j == ' ' &&  game->map[i][j])
			j++;
		j++;
		ptr = mlx_png_file_to_image(game->mlx, &game->map[i][j], &LOL, &LOL);
		if(!ptr)
			ft_error_exit("error3\n");
	}
	else if (game->map[j][0] == 'E')
	{
		j = 2;
		while(j == ' ' &&  game->map[i][j])
			j++;
		j++;
		ptr = mlx_png_file_to_image(game->mlx, &game->map[i][j], &LOL, &LOL);
		if(!ptr)
			ft_error_exit("error4\n");
	}
	
}

void checkElement(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while(game->map[i])
	{
		j = 0;
		while(game->map[i][j])
		{
			if(game->map[i][0] == 'N' && game->map[i][1] == 'O')
			{
				game->ply_map->NO++;
				checkitValid(game, i);
			}
			else if(game->map[i][0] == 'S' && game->map[i][1] == 'O')
			{
				game->ply_map->SO++;
				checkitValid(game, i);
			}
			else if(game->map[i][0] == 'W' && game->map[i][1] == 'E')
			{
				game->ply_map->WE++;
				checkitValid(game, i);
			}
			else if(game->map[i][0] == 'C' && game->map[i][1] == ' ')
			{
				game->ply_map->C++;
				checkitValid(game, i);
			}
			else if(game->map[i][0] == 'F' && game->map[i][1] == ' ')
			{
				game->ply_map->F++;
				checkitValid(game, i);
			}
			j++;
		}
		i++;
	}
	// if(game->ply_map->NO != 1 || game->ply_map->SO != 1 || game->ply_map->WE != 1 || game->ply_map->C != 1 || game->ply_map->F != 1)
	// 	ft_error_exit("error\n");
	getPlayerPosition(game);
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