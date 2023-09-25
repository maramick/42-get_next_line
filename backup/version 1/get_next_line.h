#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

//These should delete
# define BUFFER_SIZE 7
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
/////////////////////

typedef struct s_list
{
	char			*new_line;
	char			*backup;
	int				fd_id;
	struct s_list	*next;
}					t_list;

char	*ft_calloc(size_t count, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strchr(const char *s, int c);
t_list	*ft_lstadd_back(t_list **lst, int fd);
size_t	ft_lstclear_strlen(t_list **lst, char *s, int mode);
char	*get_next_line(int fd);

#endif
