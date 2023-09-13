#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include <stdio.h>
#include <string.h>

//#define BUFFER_SIZE 42

typedef struct		s_list
{
	char			*backup;
	int				lst_id;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
t_list	*ft_newnode(t_list **lst, int fd);
char	*ft_strdup(const char *s);

#endif
