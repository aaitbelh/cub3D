/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:54:38 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/06/26 18:51:55 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
#include "../mandatory/include/cub3d.h"
#define BUFFER_SIZE 20

char	*ft_strjoin_get(char *s1, char *s2);
char	*get_next_line(int fd);
int		ft_strchr_get(char *str, int c);

#endif