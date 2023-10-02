#include "get_next_line.h"

char	*ft_strcpy_nl(t_list *lst)
{
	char	*new_line;
	size_t	i;
	size_t	memory;

	if (!lst)
		return (NULL);
	i = 0;
	memory = ft_strlen_nl(lst->data, 2);
	if (memory == 0)
		return (NULL);
	new_line = (char *)malloc(memory + 1);
	if (!new_line)
		return (NULL);
	while (lst->data[i] != '\0' && lst->data[i] != '\n')
	{
		new_line[i] = lst->data[i];
		i++;
	}
	if (lst->data[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	lst = ft_update_backup(lst, new_line);
	if (!lst)
		return (NULL);
	return (new_line);
}

char	*ft_join_string(char *old_str, char *buf)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	temp = ft_checkread_malloc_t(old_str, buf, 2);
	if (temp != NULL)
	{
		while (old_str[i] != '\0')
		{
			temp[i] = old_str[i];
			i++;
		}
		while (buf[j] != '\0')
		{
			temp[i] = buf[j];
			i++;
			j++;
		}
		temp[i] = '\0';
	}
	free(old_str);
	return (temp);
}

t_list	*ft_readline(int fd, t_list *lst)
{
	char	*buf;
	int		rd;

	rd = 1;
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (1)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
			break ;
		buf[rd] = 0;
		lst->data = ft_join_string(lst->data, buf);
		if (!lst->data)
		{
			free(buf);
			return (NULL);
		}
		if (!ft_checkread_malloc_t(lst->data, buf, 1))
			break ;
	}
	free(buf);
	return (lst);
}

t_list	*ft_current_fd(int fd, t_list *lst)
{
	t_list	*current;

	current = lst;
	while (1)
	{
		if (!current)
		{
			current = ft_newnode(fd, &lst);
			if (!current)
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
	static t_list	*lst = NULL;
	t_list			*c_lst;
	char			*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (fd > 0 && lst)
			lst = ft_clearnode_eof(ft_current_fd(fd, lst));
		return (NULL);
	}
	c_lst = ft_current_fd(fd, lst);
	if (!c_lst)
		return (NULL);
	if (!lst)
		lst = c_lst;
	new_line = ft_strcpy_nl(ft_readline(fd, c_lst));
	if (!new_line)
	{
		lst = ft_clearnode_eof(c_lst);
		return (NULL);
	}
	return (new_line);
}
