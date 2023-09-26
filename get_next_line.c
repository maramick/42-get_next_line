#include "get_next_line.h"
//joining string
	//start_node possibility
		//\nABC -> cut \n and start with ABC
		//AB\nC -> cut AB\n and start with C
		//ABC\n -> start with new node
		//\nABC\n -> cut \n and start with ABC\n
		//ABC\0 -> start with this node and clear list
		//\0 -> return NULL
	//end_node possibility
		//\nABC -> contacenate only \n
		//AB\nC -> contacenate only AB\n
		//ABC\n -> contacenate this node
		//\nABC\n -> contacenate only \n
		//ABC\0 -> contacenate this node and clear list
		//\0 -> contacenate this node and clear list
//ideal is
//check start node
//join buffer loop
//check end node
//join end node
//return value
char	*ft_join_buffer(t_buflist *start_node, t_buflist *end_node)
{
	char		*str;
	size_t		i;

	str = NULL;
	i = 0;
	printf("contacenating %p->%p\n", start_node, end_node);
	//check start node
	if (start_node->buffer[i] == '\0')
		return (NULL);
	while (start_node->buffer[i] != '\0' && start_node->buffer[i] != '\n')
		i++;

	return (str);
}

void	*ft_readline(t_buflist *node, int fd)
{
	int		rd_buf;

	rd_buf = 1;
	while (rd_buf > 0 && node != NULL)
	{
		rd_buf = read(fd, node->buffer, BUFFER_SIZE);
		//checking read failed
		//rd_buf = -1;
		if (rd_buf == -1)
		{
			ft_clearnode(&node);
			return (NULL);
		}
		node->buffer[rd_buf] = 0;
		node->next = ft_newnode();
		//node allocate failed
		//node->next = NULL;
		if (!node->next)
		{
			ft_clearnode(&node);
			return (NULL);
		}
		if (ft_strchr(node->buffer, '\n') != NULL && ft_strchr(node->buffer, '\0') != NULL)
			break ;
		node = node->next;
	}
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
			//new_lst for new_fd allocate failed check
			//current = NULL;
			if(!current)
				return (NULL);
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
	char				*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (!lst)
			/*clear list*/
		return (NULL);
	}
	if (!lst)
		lst = ft_addfd_back(&lst, fd);
	//starter lst allocate failed check
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
	new_line = ft_join_buffer(begin_read, current_fd->read_data);
	return (new_line);
}
