#include "get_next_line.h"
//joining string
	//start_node possibility check until find newline or EOF
		//\nABC ->
		//AB\nC ->
		//ABC\n ->
		//\nABC\n ->
		//ABC\0 ->
		//EOF IS -> happen when starting buffer with '\0'
	//end_node possibility check until find newline or EOF
		//\nABC ->
		//AB\nC ->
		//ABC\n ->
		//\nABC\n ->
		//ABC\0 ->
		//EOF IS -> happen when starting buffer with '\0'
//ideal is
//check start node
//join buffer loop
	//idea is count all character in datastructure
	//malloc all character
	//memmove all character
//check end node
//join end node and set pointer to newbegining
//return value

char	*ft_join_buffer(t_buflist *start_node, t_buflist *end_node)
{
	//char		*str = NULL;
	size_t		i;
	size_t		count_char;

	printf("starting : %s\n", start_node->buffer);
	count_char = 0;
	if (start_node->buffer[0] == '\0')
	{
		/*reaching EOF*/
		/*This should be clear all node and destroy struct of this current fd*/
		return (NULL);
	}
	while (start_node != NULL)
	{
		i = 0;
		while(start_node->buffer[i] != '\n' && start_node->buffer[i] != '\0')
		{
			count_char++;
			i++;
		}
		if (start_node->buffer[i] == '\0')
			start_node = start_node->next;
		else if (start_node->buffer[i] == '\n')
			break;
	}
	end_node = start_node + i;
	printf("ending |%s|\n", end_node->buffer);
	printf("total character : %zu\n", count_char);
	return (NULL);
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
		if (node->buffer[0] == '\0')
			break;
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
		return (NULL);
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
