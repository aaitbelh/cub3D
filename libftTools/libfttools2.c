/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfttools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:04:50 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/07/28 14:38:35 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	allnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int						i;
	int						sig;
	unsigned long long int	n;

	sig = 1;
	n = 0;
	i = 0;
	if (allnum(str) == 0)
		return (-1);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+' )
	{
		if (str[i] == '-')
			sig *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(n * sig));
}
