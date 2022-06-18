/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfttools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:04:50 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/18 18:18:10 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned int	i;
	size_t			j;

	j = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	ptr = (char *)malloc((sizeof(char) * len + 1));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			ptr[j++] = s[i];
		}
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}

static int	len_back(const char *s1, const char *s2)
{
	int	i;
	int	len;
	int	def;
	int	h;

	def = 0;
	len = ft_strlen(s1) - 1;
	while (*(s1 + len) && len > 0)
	{
		h = 0;
		i = 0;
		while (s2[i])
		{
			if (*(s1 + len) == s2[i])
				h = 1;
			i++;
		}
		if (h == 1)
			def++;
		else
			break ;
		len--;
	}
	return (def);
}

static int	len_front(const char *s1, const char *s2)
{
	int	i;
	int	def;
	int	h;

	def = 0;
	while (*s1)
	{
		h = 0;
		i = 0;
		while (s2[i])
		{
			if (*s1 == s2[i])
				h = 1;
			i++;
		}
		if (h == 1)
			def++;
		else
			break ;
		s1++;
	}
	return (def);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len_f;
	int		len_b;
	int		len_s;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	len_f = len_front(s1, set);
	len_b = len_back(s1, set);
	len_s = ft_strlen(s1) - (len_f + len_b);
	return (ft_substr(s1, len_f, len_s));

}