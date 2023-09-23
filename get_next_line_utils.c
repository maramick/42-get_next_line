#include "get_next_line.h"

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

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*cvt_dst;
	const char	*cvt_src;

	cvt_src = (const char *)src;
	cvt_dst = (char *)dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst > src && dst < src + len)
	{
		cvt_src = cvt_src + len;
		cvt_dst = cvt_dst + len;
		while (len-- > 0)
			*(--cvt_dst) = *(--cvt_src);
	}
	else
	{
		while (len-- > 0)
			*(cvt_dst++) = *(cvt_src++);
	}
	return (dst);
}

char	*ft_calloc(size_t count, size_t size)
{
	size_t	max;
	size_t	i;
	char	*temp;

	i = 0;
	max = SIZE_MAX;
	if (count == INT_MAX && size == INT_MAX)
		return (NULL);
	if (count > (max / size))
		return (NULL);
	temp = (char *)malloc(count * size);
	if (temp == NULL)
		return (NULL);
	while (i != (count * size))
	{
		temp[i] = 0;
		i++;
	}
	return (temp);
}

size_t	ft_lstclear_strlen(char *s, int mode, t_list **lst)
{
	t_list	*current;
	t_list	*next;
	size_t	i;

	i = 0;
	if (mode == 0)
	{
		if (!lst)
			return (0);
		current = *lst;
		next = NULL;
		while (current != NULL)
		{
			next = current->next;
			printf("start freeing  ");
			printf("freeing in addr backup %p\n", current->backup);
			if (current->backup != NULL)
				free(current->backup);
			printf("freed back  ");
			free(current);
			printf("freed node");
			current = next;
		}
		*lst = NULL;
		return (0);
	}
	while (s != NULL && s[i] != '\0')
		i++;
	return (i);
}

t_list	*ft_lstadd_back(t_list **lst, int fd)
{
	t_list	*current;
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->backup = (char *)ft_calloc(1, 1);
	if (!new_node->backup)
	{
		free(new_node);
		return (NULL);
	}
	new_node->fd_id = fd;
	new_node->next = NULL;
	new_node->read_line = NULL;
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
