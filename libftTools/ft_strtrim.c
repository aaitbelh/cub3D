/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:45:52 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/27 10:57:16 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/include/cub3d.h"
#include "../bonus/include/cub3d_bonus.h"


int	count_lenb(char *s1, char c)
{
	int	i;
	int	len;

	i = ft_strlen(s1) - 1;
	len = 0;
	while (i > 0 && s1[i] == c)
	{
		i--;
		len ++;
	}
	return (len);
}

int	count_lenf(char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == c)
		i++;
	return (i);
}

char	*ft_strtrim(char *s1, char c)
{
	int		len_f;
	int		len_b;
	int		i;
	char	*new;

	len_f = count_lenf(s1, c);
	len_b = count_lenb(s1, c);
	if (len_b == 0 && len_f == 0)
		return (ft_strdup(s1));
	new = malloc(sizeof(char ) * (ft_strlen(s1) - (len_b + len_f) + 1));
	i = 0;
	while (i <= ft_strlen(s1) - (len_f + len_b) - 1)
	{
		new[i] = s1[len_f + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
