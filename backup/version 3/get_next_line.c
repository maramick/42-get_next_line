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

size_t	ft_total_char(t_buflist *start_node)
{
	size_t	i;
	size_t	total_char;

	total_char = 0;
	while (start_node != NULL)
	{
		i = 0;
		while(start_node->buffer[i] != '\0')
		{
			total_char++;
			i++;
			if (start_node->buffer[i - 1] == '\n')
				break;
		}
		if (start_node->buffer[i - 1] == '\n')
			break;
		start_node = start_node->next;
	}
	return (total_char);
}

char	*ft_join_buffer(t_buflist *start_node)
{
	char			*line;
	size_t			i;
	size_t			j;

	line = malloc(ft_total_char(start_node) + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (start_node && start_node->buffer)
	{
		j = 0;
		while ((start_node->buffer)[j] && (i == 0 || line[i - 1] != '\n'))
			line[i++] = (start_node->buffer)[j++];
		start_node = start_node->next;
	}
	line[i] = '\0';
	return (line);
}

void	*ft_readline(t_buflist *node, t_buflist *begin, int fd)
{
	int		rd_buf;

	rd_buf = 1;
	if (begin && begin->buffer[0] == '\n')
		return (node);
	if (begin != NULL && begin->buffer[0] != '\0')
	{
		begin->next = ft_newnode();
		if (!begin->next)
			return (NULL);
		node = begin->next;
	}
	while (rd_buf > 0 && node != NULL)
	{
		rd_buf = read(fd, node->buffer, BUFFER_SIZE);
		if (rd_buf == -1)
			return (NULL);
		node->buffer[rd_buf] = 0;
		if (ft_strchr(node->buffer, '\n') != NULL && ft_strchr(node->buffer, '\0') != NULL)
			break ;
		node->next = ft_newnode();
		if (!node->next)
			return (NULL);
		node = node->next;
	}
	if (begin->buffer[0] == '\0')
		return (NULL);
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
		/*we have to clear the current fd list*/
		return (NULL);
	}
	if (!lst)
		lst = ft_addfd_back(&lst, fd);
	if (!lst)
		return (NULL);
	current_fd = ft_get_startfd(lst, fd);
	if (!current_fd)
		return (NULL);
	begin_read = current_fd->read_data;
	if (ft_readline(begin_read, begin_read, fd))
		new_line = ft_join_buffer(begin_read);
	else
		new_line = NULL;
	ft_clearnode(begin_read, current_fd);
	lst = clean_fd_list(lst, current_fd);
	return (new_line);
}
