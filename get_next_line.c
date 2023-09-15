#include "get_next_line.h"

char	*ft_join_string(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	// printf("LINE_free: %p\n", s1);
	// printf("NEWLINE_mal: %p\n", temp);
	free(s1);
	if (!temp)
		return (NULL);
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
	line_temp = (char *)malloc((i + 1 + (line[i] == '\n')));
	if (line_temp == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		line_temp[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		line_temp[i++] = '\n';
	}
	//printf("line+1 = %d\n", *(line + i));
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
			break ;
	}
	return (line);
}

char	*ft_getline(t_list **lst_addr, int fd, char *buf)
{
	char	*line;
	t_list	*lst;

	lst = *lst_addr;
	// printf("\nLST ADR :%p\n", lst);
	// printf("\nSTART BACKUP :%p\n", lst->backup);
	// printf("\nbackup : %s\n", lst->backup);
	if (!lst->backup)
	{
		//printf("->Here<-\n");
		//lst->backup = ft_strdup("");
		line = (char *)calloc(1 , 1);
		line = read_file(line, buf, fd);
	}
	else
	{
		line = ft_strdup(lst->backup);
		line = read_file(line, buf, fd);
	}
	// printf("\n\nBUF_free: %p\n", buf);
	// printf("NEWLINE_free: %p\n", line);
	// printf("BACKUP_free: %p\n", lst->backup);
	// printf("LST_free: %p\n", lst);
	if (line == NULL || line[0] == '\0')
	{
		free(buf);
		free(line);
		free(lst->backup);
			//lst->backup = NULL;
		free(lst);
		*lst_addr = NULL;
		return (NULL);
	}
	//printf("\n-->Here<--\n");
	free(lst->backup);
	//lst->backup = NULL;
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
	//printf("BUF_mal: %p\n", buf);
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
			return (ft_getline(&lst, fd, buf));
		}
		if (lst)
		{
			if (lst->fd_id == fd)
				return (ft_getline(&lst, fd, buf));
		}

		lst = lst->next;
	}
	return (NULL);
	//NEW VERSION//
	// lst = ft_newnode(&lst, fd);
	// if (!lst)
	// {
	// 	free(buf);
	// 	return (NULL);
	// }
	// return (ft_getline(lst, fd, buf));
}

// int	main(void)
// {
// 	char	*file1 = "hello.txt";
// 	char	*file2 = "empty.txt";
// 	char	*file3 = "1char.txt";
// 	char	*file4 = "giant_line.txt";
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	int		fd4;

// 	fd1 = open(file1, O_RDONLY);
// 	if (fd1 == -1)
// 		return (0);
// 	fd2 = open(file2, O_RDONLY);
// 	if (fd2 == -1)
// 		return (0);
// 	fd3 = open(file3, O_RDONLY);
// 	if (fd3 == -1)
// 		return (0);
// 	fd4 = open(file4, O_RDONLY);
// 	if (fd4 == -1)
// 		return (0);

// 	printf("--------\n");
// 	printf("result : %s\n\n", get_next_line(fd3));
// 	printf("--------\n");
// 	printf("result : %s\n\n", get_next_line(fd3));
// 	printf("--------\n");
// 	printf("result : %s\n\n", get_next_line(fd3));
// 	// printf("result : %s\n", get_next_line(fd2));
// 	// printf("result : %s\n", get_next_line(fd2));
// 	return (0);
// }
