#include "get_next_line.h"

char	*ft_join_string(char *s1, char *s2)
{
	char	*temp;

	if (s1 == NULL)
	{
		s1 = ft_strdup("");
		if (!s1)
			return (NULL);
	}
	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	free(s1);
	return (temp);
}

char	*ft_extract_string(char *line, t_list *lst)
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
		i++;
	}
	if (line[i] == '\n')
		line_temp[i++] = '\n';
	lst->backup = ft_strdup(line + i);
	line_temp[i] = '\0';
	free(line);
	return (line_temp);
}

char	*read_file(char *line, char *buf, int fd)
{
	int	rd_buf;
	int	check;

	rd_buf = 1;
	check = 1;
	if (line == NULL)
		return (NULL);
	while (rd_buf > 0 && check == 1)
	{
		rd_buf = read(fd, buf, BUFFER_SIZE);
		if (rd_buf == -1)
			return (NULL);
		buf[rd_buf] = '\0';
		line = ft_join_string(line, buf);
		if (line == NULL)
			return (NULL);
		if (ft_strchr(buf, '\n') != NULL && ft_strchr(buf, '\0') != NULL)
			check = 0;
	}
	return (line);
}

char	*ft_getline(t_list *lst, int fd, char *buf)
{
	char	*line;

	if (lst->backup == NULL)
		lst->backup = ft_strdup("");
	line = ft_strdup(lst->backup);
	line = read_file(line, buf, fd);
	if (line == NULL || *line == '\0')
	{
		free(buf);
		free(line);
		free(lst->backup);
		free(lst);
		return (NULL);
	}
	free(lst->backup);
	free(buf);
	return (ft_extract_string(line, lst));
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	char			*buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	// if (lst == NULL)
	// 	printf("\nYeah NEW node\n");
	// else if (lst != NULL)
	// 	printf("\nYeah OLD node\n");
	while (1)
	{
		if (!lst)
		{
			lst = ft_newnode(&lst, fd);
			if (!lst)
			{
				free(buf);
				return (NULL);
			}
			return (ft_getline(lst, fd, buf));
		}
		if (lst->fd_id == fd)
			return (ft_getline(lst, fd, buf));
		lst = lst->next;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	*file1 = "hello.txt";
// 	char	*file2 = "empty.txt";
// 	int		fd1;
// 	int		fd2;

// 	fd1 = open(file1, O_RDONLY);
// 	if (fd1 == -1)
// 		return (0);
// 	fd2 = open(file2, O_RDONLY);
// 	if (fd2 == -1)
// 	{
// 		printf("can't open files");
// 		return (0);
// 	}
// 	printf("result : %s\n", get_next_line(fd2));
// 	printf("result : %s\n", get_next_line(fd2));
// 	printf("result : %s\n", get_next_line(fd2));
// 	printf("result : %s\n", get_next_line(fd2));
// 	return (0);
// }
