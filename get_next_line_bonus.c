#include "get_next_line_bonus.h"

static t_lst	**get_fd_storage(t_fd **head, int fd)
{
	t_fd	*cur;
	t_fd	*new_node;

	cur = *head;
	while (cur)
	{
		if (cur->fd == fd)
			return (&cur->chunks);
		cur = cur->next;
	}
	new_node = (t_fd *)malloc(sizeof(t_fd));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->chunks = NULL;
	new_node->next = *head;
	*head = new_node;
	return (&(*head)->chunks);
}

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
	static t_fd	*fds;
	t_lst		**storage;
	char		*buf;
	char		*line;
	int			rd;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = get_fd_storage(&fds, fd);
	if (!storage)
		return (NULL);
	rd = 1;
	while (!has_newline(*storage) && rd > 0)
	{
		buf = (char *)malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (NULL);
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd < 0)
		{
			free(buf);
			lst_clear(storage);
			return (NULL);
		}
		buf[rd] = '\0';
		if (rd > 0)
			lst_add_back(storage, lst_new(buf));
		else
			free(buf);
	}
	if (!*storage)
		return (NULL);
	line = extract_line(storage);
	if (*storage && my_strchr((*storage)->str, '\n'))
		shift_after_newline(storage);
	return (line);
}
