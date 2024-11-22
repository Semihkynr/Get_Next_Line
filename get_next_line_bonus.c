/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:41:01 by skaynar           #+#    #+#             */
/*   Updated: 2024/11/22 16:52:16 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char *ft_before(char *repo)
{
    int i;
    char *line;
    
    i = 0;
    if (!repo[i])
        return (NULL);
    while (repo[i] && repo[i] != '\n')
        i++;
    line = (char *)malloc(sizeof(char) * (i + 2));
    if (!line)
        return (NULL);
    i = 0;
    while (repo[i] && repo[i] != '\n')
    {
        line[i] = repo[i];
        i++;
    }
    if (repo[i] == '\n')
    {
        line[i] = repo[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}

static char *ft_after(char *repo)
{
    int i;
    int j;
    char *new_repo;

    i = 0;
    while (repo[i] && repo[i] != '\n')
        i++;
    if (!repo[i])
    {
        free(repo);
        return (NULL);
    }
    new_repo = (char *)malloc(sizeof(char) * (ft_strlen(repo) - i + 1));
    if (!repo)
        return (NULL);
    i++;
    j = 0;
    while (repo[i])
        new_repo[j++] = repo[i++];
    new_repo[j] = '\0';
    free(repo);
    return (new_repo);
}

static char *ft_join(char *repo, char *buffer, int fd)
{
    int count;

    count = 1;
    while (!ft_strchr(repo, '\n') && count != 0)
    {
        count = read(fd, buffer, BUFFER_SIZE);
        if (count == -1)
        {
            free(buffer);
            free(repo);
            return (NULL);
        }
        buffer[count] = '\0';
        repo = ft_strjoin(repo, buffer);
    }
    free(buffer);
    return (repo);
}
char *get_next_line(int fd)
{
    char *line;
    char *buffer;
    static char *repo[1024];

    if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
        return (NULL);
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    repo[fd] = ft_join(repo[fd], buffer, fd);
    if (!repo[fd])
        return (NULL);
    line = ft_before(repo[fd]);
    repo[fd] = ft_after(repo[fd]);
    return (line);
}
