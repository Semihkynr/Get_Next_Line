/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:29:35 by skaynar           #+#    #+#             */
/*   Updated: 2024/11/22 18:33:23 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	i;

	i = (char)c;
	if (!s)
		return (0);
	if (i == '\0')
		return ((char *)s);
	while (*s)
	{
		if (*s == i)
			return ((char *)s);
		s++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*area;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		s1[0] = 0;
	}
	area = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!area)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		area[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		area[i++] = s2[j++];
	area[i] = '\0';
	free(s1);
	return (area);
}
