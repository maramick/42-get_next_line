#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

//These should delete
//# define BUFFER_SIZE 1
# include <fcntl.h>
# include <stdio.h>
//# include <string.h>
# include <stdint.h>
/////////////////////

typedef struct s_list
{
	char			*data;
	int				fd_id;
	struct s_list	*next;
}					t_list;

//void	free(void *p);
//void	*malloc(size_t size);
t_list	*ft_clearnode_eof(t_list *lst);
void	*ft_update_backup(t_list *c_lst);
size_t	ft_strlen_nl(char *s, size_t mode);
int		ft_check_read(char *s);
t_list	*ft_newnode(int fd, t_list **lst);
char	*get_next_line(int fd);

#endif
