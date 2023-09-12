#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	s_len;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	dup = (char *)malloc((s_len * sizeof(char)) + 1);
	if (dup == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
//We should remove this function//
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
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*temp;
	size_t		size_s1;
	size_t		size_s2;
	char const	*s;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 != NULL && s2 != NULL)
	{
		size_s1 = ft_strlen(s1);
		size_s2 = ft_strlen(s2);
		temp = (char *)malloc(((size_s1) + (size_s2) + 1));
		if (temp == NULL)
			return (NULL);
		ft_memmove(temp, s1, size_s1);
		ft_memmove(temp + size_s1, s2, size_s2);
		temp[size_s1 + size_s2] = '\0';
		return (temp);
	}
	temp = ft_strdup(s);
	if (temp == NULL)
		return (NULL);
	return (temp);
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

t_list	*ft_newnode(t_list **lst, int fd)
{
	t_list *new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->lst_id = fd;
	new_node->backup = NULL;
	new_node->next = *lst;
	*lst = new_node;
	return (new_node);
}

