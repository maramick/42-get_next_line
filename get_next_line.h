#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 10

typedef struct		s_list
{
	char			*content;
	int				lst_id;
	struct s_list	*next;
}					t_list;

t_list	*ft_newnode(t_list **lst, int fd);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strchr(const char *s, int c);


#endif
