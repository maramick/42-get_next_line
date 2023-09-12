#include "./get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	size_t	size_s1;
	size_t	size_s2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
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

char	*add_and_free_strjoin(char *s1, char *s2)
{
	char	*temp;
	size_t	size_s1;
	size_t	size_s2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	temp = (char *)malloc(((size_s1) + (size_s2) + 1));
	if (temp == NULL)
		return (NULL);
	ft_memmove(temp, s1, size_s1);
	ft_memmove(temp + size_s1, s2, size_s2);
	temp[size_s1 + size_s2] = '\0';
	free(s1);
	return (temp);
}

char	*read_line(int fd)
{
	int		read_buf;
	int		check;
	char	*temp;
	char	*c;

	check = 0;
	read_buf = 1;
	//Allocate for c
	c = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (c == NULL)
		return (NULL);
	//Allocate for temp
	temp = (char *)calloc(1, 1);
	if (temp == NULL)
		return (NULL);
	//Read files until find NL or EOF
	while (read_buf > 0 && check != 1)
	{
		read_buf = read(fd, c, BUFFER_SIZE);
		if (read_buf == -1)
		{
			free(c);
			return (NULL);
		}
		temp = add_and_free_strjoin(temp, c);
		if (temp == NULL)
			return (NULL);
		if (ft_strchr(c, '\n') != NULL || ft_strchr(c, '\0') != NULL)
			check = 1;
	}
	free(c);
	return (temp);
}

char	*get_line(int fd, t_list **lst)
{
	int		i;
	char	*line;
	char	*temp;
	t_list	*current;

	i = 0;
	current = *lst;
	//Copy full buffer until NL or EOF
	temp = read_line(fd);
	if (temp == NULL)
		return (NULL);
	//Count line
	if (ft_strchr(temp, '\n') != NULL)
	{
		//For NL
		line = (char *)calloc((ft_strchr(temp, '\n') - temp + 1 + 1), 1);
		if (line == NULL)
			return (NULL);
		while (temp[i] && temp[i] != '\n')
		{
			line[i] = temp[i];
			i++;
		}
		line[i] = '\n';
		current->content = strdup(ft_strchr(temp, '\n') + 1);
	}
	else
	{
		line = strdup(temp);
		current->content = NULL;
	}
	free(temp);
	return (line);
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
			new_line = get_line(fd, &lst);
			printf("line => %s|\n", new_line);
			printf("save content => %d|\n", lst->lst_id);
			printf("save content => %s|\n", lst->content);
			return (0);
		}
		current = current->next;
	}
	//Create new node if this is new fd
	printf("This is New list\n");
	new_node = ft_newnode(&lst, fd);
	if (!new_node)
		return (NULL);
	new_line = get_line(fd, &lst);
	if (new_line == NULL)
		return (NULL);
	printf("line => %s|\n", new_line);
	printf("save content => %d|\n", lst->lst_id);
	printf("save content => %s|\n", lst->content);
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
