#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

//These should delete
//# define BUFFER_SIZE 30
# include <fcntl.h>
# include <stdio.h>
/////////////////////

typedef struct s_list
{
	char			*backup;
	int				fd_id;
	struct s_list	*next;
}					t_list;

char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
t_list	*ft_newnode(t_list **lst, int fd);
char	*get_next_line(int fd);

#endif
