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
	if (!buf)
		return (NULL);
	if (!node)
		node = ft_newnode(strdup(""));
	while (rd_buf > 0 && node != NULL)
	{
		rd_buf = read(fd, buf, BUFFER_SIZE);
		if (rd_buf == -1)
			break;
		buf[rd_buf] = 0;
		node->next = ft_newnode(buf);
		if (!node->next)
			break;
		node = node->next;
		if (ft_strchr(buf, '\n') != NULL && ft_strchr(buf, '\0') != NULL)
			break ;
	}
	free(buf);
	return (node);
}

t_fdlist	*ft_get_dtstruct(t_fdlist *lst, int fd)
{
	t_fdlist	*current;
	t_buflist	*begin_node;

	current = lst;
	while (1)
	{
		if (!current)
		{
			current = ft_addfd_back(&lst, fd);
			current->read_data = NULL;
			if(!current)
			{
				/*free lst function*/
				return (NULL);
			}
			break ;
		}
		if (current->fd_id == fd)
			break ;
		current = current->next;
	}
	begin_node = current->read_data;
	current->read_data = ft_readline(begin_node, fd);
	return (current);
}

char	*get_next_line(int fd)
{
	static t_fdlist		*lst = NULL;
	t_fdlist			*current;
	//char				*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (!lst)
			/*clear list*/
		return (NULL);
	}
	current = lst;
	if (!lst)
	{
		lst = ft_addfd_back(&lst, fd);
		if (!lst)
			return (NULL);
	}
	current = ft_get_dtstruct(lst, fd);
	return (NULL);
}
