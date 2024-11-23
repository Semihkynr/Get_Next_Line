/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:41:13 by skaynar           #+#    #+#             */
/*   Updated: 2024/11/23 15:00:39 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

size_t		ft_strlen(const char *str);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char *s1, char *s2);
char		*get_next_line(int fd);

#endif
