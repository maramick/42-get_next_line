#include "get_next_line.h"

t_list	*ft_newnode(t_list **lst, int fd)
{
	t_list *new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->lst_id = fd;
	new_node->content = NULL;
	new_node->next = *lst;
	*lst = new_node;
	return (new_node);
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

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
