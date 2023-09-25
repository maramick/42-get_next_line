#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

//These should delete
//# define BUFFER_SIZE 1
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
/////////////////////

typedef struct s_list
{
	char			*backup;
	char			*read_line;
	int				fd_id;
	struct s_list	*next;
}					t_list;

char	*ft_strchr(const char *s, int c);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_calloc(size_t count, size_t size);
t_list	*ft_lstadd_back(t_list **lst, int fd);
size_t	ft_lstclear_strlen(char *s, int mode, t_list **lst);
char	*get_next_line(int fd);

#endif
