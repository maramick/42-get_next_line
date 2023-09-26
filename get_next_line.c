#include "get_next_line.h"

// char	*ft_join_buffer(t_buflist *node)
// {
// 	char	*temp;
// }

void	*ft_readline(t_buflist *node, int fd)
{
	int		rd_buf;
	char	*buf;

	rd_buf = 1;
	buf = (char *)malloc(BUFFER_SIZE + 1);
	//buff allocate failed check
	//buf = NULL;
	if (!buf)
		return (NULL);
	if (!node)
		node = ft_newnode(strdup(""));
	//node allocate failed check
	//node = NULL;
	while (rd_buf > 0 && node != NULL)
	{
		rd_buf = read(fd, buf, BUFFER_SIZE);
		//read failed check
		//rd_buf = -1;
		if (rd_buf == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rd_buf] = 0;
		node->next = ft_newnode(buf);
		//node allocate failed check
		//node->next = NULL;
		if (!node->next)
		{
			ft_clearnode(&node);
			break;
		}
		node = node->next;
		if (ft_strchr(buf, '\n') != NULL && ft_strchr(buf, '\0') != NULL)
			break ;
	}
	free(buf);
	return (node);
}

t_fdlist	*ft_get_startfd(t_fdlist *lst, int fd)
{
	t_fdlist	*current;

	current = lst;
	while (1)
	{
		if (!current)
		{
			current = ft_addfd_back(&lst, fd);
			//lst allocate failed check
			//current = NULL;
			if(!current)
				return (NULL);
			current->read_data = NULL;
			break ;
		}
		if (current->fd_id == fd)
			break ;
		current = current->next;
	}
	return (current);
}

char	*get_next_line(int fd)
{
	static t_fdlist		*lst = NULL;
	t_fdlist			*current_fd;
	t_buflist			*begin_read;
	//char				*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (!lst)
			/*clear list*/
		return (NULL);
	}
	if (!lst)
		lst = ft_addfd_back(&lst, fd);
	//lst allocate failed check
	//lst = NULL;
	if (!lst)
		return (NULL);
	current_fd = ft_get_startfd(lst, fd);
	if (!current_fd)
		return (NULL);
	begin_read = current_fd->read_data;
	current_fd->read_data = ft_readline(begin_read, fd);
	if (!current_fd->read_data)
		return (NULL);
	printf("begin_read : %p\n", begin_read);
	printf("update_read : %p\n", current_fd->read_data);
	return (NULL);
}
