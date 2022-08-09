/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:48:55 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/08/09 16:56:50 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

int	update(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	ray_casting(game);
	return (1);
}

int	render(t_game *game)
{
	if (game->player->tab[13])
		move_up(game);
	if (game->player->tab[1])
		move_down(game);
	if (game->player->tab[124])
		rotate_right(game);
	if (game->player->tab[123])
		rotate_left(game);
	if (game->player->tab[2])
		move_right(game);
	if (game->player->tab[0])
		move_left(game);
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
	initializedata(av, data);
	mlx_hook(data->win, 02, 1L, key_released, data);
	mlx_hook(data->win, 03, 2L, key_pressed, data);
	mlx_hook(data->win, 17, 0, redcross, NULL);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
}
