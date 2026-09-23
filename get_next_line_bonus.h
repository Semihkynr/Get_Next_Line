#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_lst
{
	char			*str;
	struct s_lst	*next;
}	t_lst;

typedef struct s_fd
{
	int				fd;
	t_lst			*chunks;
	struct s_fd		*next;
}	t_fd;

size_t	my_strlen(const char *s);
char	*my_strchr(const char *s, int c);
char	*my_strdup(const char *s);
t_lst	*lst_new(char *str);
void	lst_add_back(t_lst **lst, t_lst *new_node);
void	lst_clear(t_lst **lst);
char	*get_next_line(int fd);

#endif
