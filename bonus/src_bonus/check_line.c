/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:28:23 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/08/08 19:17:07 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_newline(char *buf, int *lock)
{
	char	*tmp;

	tmp = ft_strtrim(buf, ' ');
	if (tmp[0] == '1' && !*lock)
		*lock = 1;
	if (*lock == 1 && tmp[0] == '\n')
		*lock = 2;
	if (*lock == 2 && tmp[0] == '1')
		*lock = 3;
	free(tmp);
	if (*lock == 3)
		ft_error_exit("a line in the midle of the map\n");
}
