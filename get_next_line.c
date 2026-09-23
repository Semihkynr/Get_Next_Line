#include "get_next_line.h"

static int	has_newline(t_lst *lst)
{
	while (lst)
	{
		if (my_strchr(lst->str, '\n'))
			return (1);
		lst = lst->next;
	}
	return (0);
}

static size_t	line_length(t_lst *lst)
{
	size_t	len;
	char	*nl;

	len = 0;
	while (lst)
	{
		nl = my_strchr(lst->str, '\n');
		if (nl)
			return (len + (size_t)(nl - lst->str) + 1);
		len += my_strlen(lst->str);
		lst = lst->next;
	}
	return (len);
}

static char	*extract_line(t_lst **lst)
{
	char	*line;
	char	*nl;
	t_lst	*next_node;
	size_t	pos;
	size_t	i;

	line = (char *)malloc(line_length(*lst) + 1);
	if (!line)
		return (NULL);
	pos = 0;
	while (*lst)
	{
		nl = my_strchr((*lst)->str, '\n');
		i = 0;
		while ((*lst)->str[i] && (*lst)->str[i] != '\n')
			line[pos++] = (*lst)->str[i++];
		if (nl)
		{
			line[pos++] = '\n';
			break ;
		}
		next_node = (*lst)->next;
		free((*lst)->str);
		free(*lst);
		*lst = next_node;
	}
	line[pos] = '\0';
	return (line);
}

static void	shift_after_newline(t_lst **lst)
{
	char	*nl;
	char	*rest;
	t_lst	*next_node;
	t_lst	*new_head;

	nl = my_strchr((*lst)->str, '\n');
	next_node = (*lst)->next;
	rest = my_strdup(nl + 1);
	free((*lst)->str);
	free(*lst);
	if (rest && rest[0] != '\0')
	{
		new_head = lst_new(rest);
		new_head->next = next_node;
		*lst = new_head;
	}
	else
	{
		if (rest)
			free(rest);
		*lst = next_node;
	}
}

char	*get_next_line(int fd)
{
	static t_lst	*saved;
	char			*buf;
	char			*line;
	int				rd;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rd = 1;
	while (!has_newline(saved) && rd > 0)
	{
		buf = (char *)malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (NULL);
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd < 0)
		{
			free(buf);
			lst_clear(&saved);
			return (NULL);
		}
		buf[rd] = '\0';
		if (rd > 0)
			lst_add_back(&saved, lst_new(buf));
		else
			free(buf);
	}
	if (!saved)
		return (NULL);
	line = extract_line(&saved);
	if (saved && my_strchr(saved->str, '\n'))
		shift_after_newline(&saved);
	return (line);
}
