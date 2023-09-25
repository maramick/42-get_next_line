#include "get_next_line.h"

char	*ft_strdup(char *s)
{
	/*add function*/
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
	new_node->read_data = NULL;
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

t_buflist	*ft_newnode(void *content)
{
	t_buflist	*node;

	node = malloc(sizeof(t_buflist));
	if (node == NULL)
		return (NULL);
	node->buffer = strdup(content);
	node->next = NULL;
	return (node);
}
