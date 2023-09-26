#include "get_next_line.h"

void	ft_clearnode(t_buflist **node)
{
	t_buflist	*current;
	t_buflist	*next;

	if (!node)
		return ;
	current = *node;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current->buffer);
		current->buffer = NULL;
		current = next;
	}
	*node = NULL;
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (c == '\0')
	{
		while (*s != '\0')
			s++;
		return ((char *)s);
	}
	while (s[i] != ((char)c))
	{
		if (!s[i])
			return (NULL);
		i++;
	}
	return ((char *)(s + i));
}

t_fdlist	*ft_addfd_back(t_fdlist **lst, int fd)
{
	t_fdlist	*current;
	t_fdlist	*new_node;

	new_node = (t_fdlist *)malloc(sizeof(t_fdlist));
	if (!new_node)
		return (NULL);
	new_node->fd_id = fd;
	new_node->read_data = ft_newnode();
	if (!new_node->read_data)
	{
		free(new_node);
		return (NULL);
	}
	//add back process
	new_node->next = NULL;
	if (*lst == NULL)
	{
		*lst = new_node;
		return (*lst);
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	return (current->next);
}

//don't forget to clear buffer list

t_buflist	*ft_newnode(void)
{
	t_buflist	*node;

	node = malloc(sizeof(t_buflist));
	if (node == NULL)
		return (NULL);
	node->buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (node->buffer == NULL)
	{
		free(node);
		return (NULL);
	}
	node->buffer[0] = 0;
	node->next = NULL;
	return (node);
}
