/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:48:55 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/27 12:52:45 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d_bonus.h"


int  update(t_game *game)
{
	ray_casting(game);
	return (1);
}

int KeyReleased(int key, t_game *game)
{
	game->player->tab[key] = 1;
	if (key == 53)
		exit(0);
	return (1);
}
int KeyPressed(int key, t_game *game)
{
	game->player->tab[key] = 0;
	if (key == 53)
		exit(0);
	return (1);
}


int render(t_game *game)
{
	if(game->player->tab[13])
		move_up(game);
	if(game->player->tab[1])
		move_down(game);
	if(game->player->tab[124])
		rotate_right(game);
	if(game->player->tab[123])
		rotate_left(game);
	if(game->player->tab[2])
		move_right(game);
	if(game->player->tab[0])
		move_left(game);
	update(game);
	return (1);
}


char	**makeMapRect(t_game *game)
{
	int	i;
	int	tmp;
	int	j;
	char **new;

	i = 0;
	while(game->map[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	tmp = 0;
	tmp = ft_strlen(game->map[0]);
	i = 0;
	while(game->map[i])
	{
		if(tmp < ft_strlen(game->map[i]))
			tmp = ft_strlen(game->map[i]);
		i++;		
	}
	if(!new)
		return (NULL);
	i = 0;
	while(game->map[i])
	{
		j = 0;
		new[i] = malloc(sizeof(char) * (tmp + 1));
		while(j < tmp)
		{
			if(j < ft_strlen(game->map[i]))
			{
				new[i][j] = game->map[i][j];
			}
			else
				new[i][j] = '0';
			j++;
		}
		new[i][j] = '\0';
		i++;
	}
	new[i] = NULL;
	twodfree(game->map); 
	return (new);
} 

void	fix_map(t_game *game)
{
	int	i;
	int	j;
	
	i = 0;
	while(game->map[i])
	{
		j = 0;
		while(game->map[i][j])
		{
			if(game->map[i][j] == ' ')
				game->map[i][j] = '0';
			j++;
		}
		i++;
	}
	game->map = makeMapRect(game);
}

int redCross(int Key)
{
	(void)Key;
	exit(1);
}
int main(int ac, char **av)
{

	if(ac > 2 || ac < 2)
		ft_error_exit("not enough argument\n");
	t_game *data;
	data = malloc(sizeof(t_game));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1800 ,900, "prototype");
	initializedata(av, data);
	mlx_hook(data->win, 02, 1L, KeyReleased, data);
	mlx_hook(data->win, 03, 2L, KeyPressed, data);
	mlx_hook(data->win, 17, 0, redCross, NULL);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
}