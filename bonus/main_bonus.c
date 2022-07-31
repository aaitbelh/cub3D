/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:48:55 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/07/31 12:41:29 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	update(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	ray_casting(game);
	return (1);
}

void	mouserotation(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (game->mousestate)
	{
		mlx_mouse_get_pos(game->win, &x, &y);
		if (x > game->mousex)
			rotate_right(game);
		if (x < game->mousex)
			rotate_left(game);
		mlx_mouse_move(game->win, 900, 450);
		mlx_mouse_hide();
		game->mousex = x;
		game->mousex = 900;
		x = 900;
	}
	else
		mlx_mouse_show();
}

int	render(t_game *game)
{
	if (game->player->tab[13])
		move_up(game);
	if (game->player->tab[1])
		move_down(game);
	if (game->player->tab[2])
		move_right(game);
	if (game->player->tab[0])
		move_left(game);
	mouserotation(game);
	update(game);
	return (1);
}

int	redcross(int Key)
{
	(void)Key;
	exit(1);
}

int	main(int ac, char **av)
{
	t_game	*data;

	if (ac > 2 || ac < 2)
		ft_error_exit("not enough argument\n");
	data = malloc(sizeof(t_game));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1800, 900, "prototype");
	initializedata(av, data);
	mlx_hook(data->win, 02, 1L, key_released, data);
	mlx_hook(data->win, 03, 2L, key_pressed, data);
	mlx_hook(data->win, 17, 0, redcross, NULL);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
}
