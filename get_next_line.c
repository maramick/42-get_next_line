#include "./get_next_line.h"

//We should check if
//read data have '\n' or '\0' in string
//if have '\n'
//we should check
//-> '\n' on last character -> save == NULL
//-> '\n' on first character -> save == NULL
//-> '\n' on middile of string
char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char	*read_line(int fd, t_list *lst)
{
	char	*buf;
	char	*line_read;
	int		read_buf;
	int		check;

	check = 0;
	read_buf = 1;
	buf = (char *)calloc((BUFFER_SIZE * sizeof(char) + 1), 1);
	if (buf == NULL)
		return (NULL);
	//printf("starter backup = %s\n", lst->backup);
	line_read = ft_strdup(lst->backup);
	if (line_read == NULL)
	{
		free(buf);
		return (NULL);
	}
	while(read_buf > 0 && check == 0)
	{
		read_buf = read(fd, buf, BUFFER_SIZE);
		if (read_buf == -1)
		{
			free(buf);
			return (NULL);
		}
		//prevent leaking
		buf[read_buf] = '\0';
		//printf("copying : %s\n", buf);
		line_read = ft_free(line_read, buf);
		//printf("copying : %s\n", line_read);
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

char	*extract_string(char *line, t_list *lst)
{
	char	*line_temp;
	int		i;

	i = 0;

	while (line[i] != '\0' && line[i] != '\n')
	{
		i++;
	}
	line_temp = (char *)malloc((i + 1 + (line[i] != '\n')) * sizeof(char));
	if (line_temp == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		line_temp[i] = line[i];
		//printf("copying : %s\n", line_temp);
		i++;
	}
	if (line[i] == '\n')
		line_temp[i++] = '\n';
	lst->backup = ft_strdup(line + i);
		//printf("backup : %s\n\n", lst->backup);
	line_temp[i] = '\0';
	free(line);
	return (line_temp);
}

char	*ft_get_line(int fd, t_list *lst)
{
	char	*line;
	char	*new_line;

	if (lst->backup == NULL)
		lst->backup = strdup("");
	line = read_line(fd, lst);
	//printf("line before extract : %s\n", line);
	if (line == NULL || *line == '\0')
	{
		free(line);
		return (NULL);
	}
	free(lst->backup);
	new_line = extract_string(line, lst);
	//printf("backup : %s\n", lst->backup);
	if (new_line == NULL)
		return (NULL);
	return	(new_line);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	char			*new_line;
	t_list			*current;
	t_list			*new_node;

	new_line = NULL;
	current = lst;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	//Check this is old fd or not
	while (current != NULL)
	{
		if (current->lst_id == fd)
		{
			new_line = ft_get_line(fd, lst);
			if (new_line == NULL)
			{
				free(lst->backup);
				free(lst);
				return (NULL);
			}
			return (new_line);
		}
		current = current->next;
	}
	//Create new node if this is new fd
	new_node = ft_newnode(&lst, fd);
	if (!new_node)
		return (NULL);
	new_line = ft_get_line(fd, lst);
	if (new_line == NULL)
	{
		//leak handlie
		free(lst);
		return (NULL);
	}
	return new_line;
}

// int	main(void)
// {
// 	char*	fileName1 = "hello.txt";
// 	char*	fileName2 = "files/big_line_with_nl";
// 	char*	fileName3 = "files/multiple_line_with_nl";
// 	char*	fileName4 = "files/empty";
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	int		fd4;
// 	char	*save;

// 	fd1 = open(fileName1, O_RDONLY);
// 	if (fd1 == -1)
// 		return (0);
// 	fd2 = open(fileName2, O_RDONLY);
// 	if (fd2 == -1)
// 		return (0);
// 	fd3 = open(fileName3, O_RDONLY);
// 	if (fd3 == -1)
// 		return (0);
// 	fd4 = open(fileName4, O_RDONLY);
// 	if (fd3 == -1)
// 		return (0);

// 	printf("%d\n", fd1);
// 	printf("%d\n", fd2);
// 	printf("%d\n", fd3);
// 	save = get_next_line(fd2);
// 	//printf("result : %s\n", get_next_line(fd2));
// 	// //free(save);
// 	// //save = get_next_line(fd1);
// 	// printf("result : %s\n", get_next_line(fd2));
// 	// //free(save);
// 	// //save = get_next_line(fd1);
// 	// printf("result : %s\n", get_next_line(fd2));
// 	// printf("result : %s\n", get_next_line(fd2));
// 	// printf("result : %s\n", get_next_line(fd2));
// 	// printf("result : %s", get_next_line(fd2));
// 	//free(save);
// 	// get_next_line(fd2);
// 	// get_next_line(fd3);
// 	// get_next_line(fd1);
// 	// get_next_line(fd1);
// 	// get_next_line(fd1);
// 	// get_next_line(fd2);
// 	// get_next_line(fd3);
// 	// get_next_line(fd4);
// }
