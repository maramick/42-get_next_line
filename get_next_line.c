#include "./get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	s_len;
	size_t	i;

	i = 0;
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

//We should check if
//read data have '\n' or '\0' in string
//if have '\n'
//we should check
//-> '\n' on last character -> save == NULL
//-> '\n' on first character -> save == NULL
//-> '\n' on middile of string

char	*read_line(int fd, t_list *lst)
{
	char	*buf;
	char	*line_read;
	int		read_buf;
	int		check;

	check = 0;
	buf = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (buf == NULL)
		return (NULL);
	line_read = ft_strdup(lst->backup);
	while(read_buf > 0 && check == 0)
	{
		read_buf = read(fd, buf, BUFFER_SIZE);
		if (read_buf == -1)
		{
			free(buf);
			return (NULL);
		}
		line_read = ft_strjoin(line_read, buf);
		if (line_read == NULL)
		{
			free(line_read);
			free(buf);
			return (NULL);
		}
		if (ft_strchr(buf, '\n') != NULL && ft_strchr(buf, '\0') != NULL)
			check = 1;
	}
	free(buf);
	return (line_read);
}

char	*get_line(int fd, t_list *lst)
{
	char	*line;

	if (lst->backup == NULL)
		lst->backup = strdup("");
	line = read_line(fd, lst);
	printf("line : %s\n", line);
	printf("backup : %s\n", lst->backup);
	printf("id : %d\n", lst->lst_id);
	return	(line);
}

char	*get_next_line(int fd)
{
	char			*new_line;
	t_list			*current;
	t_list			*new_node;
	static t_list	*lst = NULL;

	new_line = NULL;
	current = lst;
	//Check this is old fd or not
	while (current != NULL)
	{
		if (current->lst_id == fd)
		{
			new_line = get_line(fd, lst);
			return (new_line);
		}
		current = current->next;
	}
	//Create new node if this is new fd
	new_node = ft_newnode(&lst, fd);
	if (!new_node)
		return (NULL);
	new_line = get_line(fd, lst);
	return new_line;
}

int	main(void)
{
	char*	fileName1 = "hello.txt";
	char*	fileName2 = "files/big_line_with_nl";
	char*	fileName3 = "files/multiple_line_with_nl";
	char*	fileName4 = "files/empty";
	int		fd1;
	int		fd2;
	int		fd3;
	int		fd4;

	fd1 = open(fileName1, O_RDONLY);
	if (fd1 == -1)
		return (0);
	fd2 = open(fileName2, O_RDONLY);
	if (fd2 == -1)
		return (0);
	fd3 = open(fileName3, O_RDONLY);
	if (fd3 == -1)
		return (0);
	fd4 = open(fileName4, O_RDONLY);
	if (fd3 == -1)
		return (0);

	printf("%d\n", fd1);
	printf("%d\n", fd2);
	printf("%d\n", fd3);
	get_next_line(fd1);
	// get_next_line(fd2);
	// get_next_line(fd3);
	// get_next_line(fd1);
	// get_next_line(fd1);
	// get_next_line(fd1);
	// get_next_line(fd2);
	// get_next_line(fd3);
	// get_next_line(fd4);

}
