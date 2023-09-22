#include "get_next_line.h"

//Check if lst is empty ?
	//if it empty just create newnode
	//if not doesn't nothing
//We should use just one data structure and void every function
	//to be handle with memmoory allocate

void	ft_extract_content(t_list *lst, char *read_line, char *buf)
{
	size_t	i;
	size_t	len_backup;

	free(buf);
	if (!read_line || !lst || *read_line == '\0')
		return ;
	i = 0;
	while (read_line[i] != '\n' && read_line[i] != '\0')
		i++;
	i = i + (read_line[i] == '\n');
	len_backup = ft_lstclear_strlen(&lst, read_line, 1) - i;
	lst->new_line = (char *)ft_calloc(i + 1, 1);
	if (!lst->new_line)
		return ;
	lst->backup = (char *)ft_calloc(len_backup + 1, 1);
	if (!lst->backup)
	{
		free(lst->new_line);
		return ;
	}
	ft_memmove(lst->new_line, read_line, i);
	ft_memmove(lst->backup, read_line + i, len_backup);
}

char	*ft_addcontent(char	*read_line, char *buf, t_list *lst)
{
	char	*temp;
	int		len_read_line;
	int		len_buf;

	len_read_line = ft_lstclear_strlen(&lst, read_line, 1);
	len_buf = ft_lstclear_strlen(&lst, buf, 1);
	temp = (char *)ft_calloc((len_read_line + len_buf + 1), 1);
	if (!temp)
	{
		free(read_line);
		return (NULL);
	}
	ft_memmove(temp, read_line, len_read_line);
	ft_memmove(temp + len_read_line, buf, len_buf);
	free(read_line);
	return (temp);
}

void	*ft_readline(t_list *lst, int fd, char *read_line)
{
	char	*buf;
	int		rd_buf;

	rd_buf = 1;
	buf = (char *)malloc(BUFFER_SIZE);
	if (!buf)
		return (NULL);
	while (rd_buf > 0)
	{
		rd_buf = read(fd, buf, BUFFER_SIZE);
		if (rd_buf == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rd_buf] = '\0';
		read_line = ft_addcontent(read_line, buf, lst);
		if (ft_strchr(buf, '\n') != NULL && ft_strchr(buf, '\0') != NULL)
			break ;
	}
	ft_extract_content(lst , read_line, buf);
	free(read_line);
	return (lst->new_line);
}

char	*get_new_newline(t_list *lst, int fd, char *read_line)
{
	t_list	*current;

	current = lst;
	while (1)
	{
		if (!current)
		{
			current = ft_lstadd_back(&lst, fd);
			if(!current)
			{
				ft_lstclear_strlen(&lst, "", 0);
				return (NULL);
			}
			break ;
		}
		if (current->fd_id == fd)
			break ;
		current = current->next;
	}
	if (!ft_readline(current, fd, read_line) || current->new_line == NULL)
	{
		free(lst);
		return (NULL);
	}
	return (current->new_line);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	char			*read_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	read_line = ft_calloc(1, 1);
	if (!read_line)
		return (NULL);
	if (!lst)
	{
		lst = ft_lstadd_back(&lst, fd);
		if (!lst)
			return (NULL);
	}
	read_line = get_new_newline(lst, fd, read_line);
	if (!read_line)
		return (NULL);
	return (read_line);
}
/*******/
//New Idead
//We have to start form backup file that should be good for anycase//
/*******/
int	main(void)
{
	char	*file1 = "hello.txt";
	char	*file2 = "empty.txt";
	char	*file3 = "1char.txt";
	char	*file4 = "giant_line.txt";
	int		fd1;
	int		fd2;
	int		fd3;
	int		fd4;

	fd1 = open(file1, O_RDONLY);
	if (fd1 == -1)
		return (0);
	fd2 = open(file2, O_RDONLY);
	if (fd2 == -1)
		return (0);
	fd3 = open(file3, O_RDONLY);
	if (fd3 == -1)
		return (0);
	fd4 = open(file4, O_RDONLY);
	if (fd4 == -1)
		return (0);

	printf("--------\n");
	printf("3 result : %s\n", get_next_line(fd1));
	printf("3 result : %s\n", get_next_line(fd1));

	// printf("2 result : %s\n\n", get_next_line(fd2));
	// printf("1 result : %s\n\n", get_next_line(fd1));
	// printf("2 result : %s\n\n", get_next_line(fd2));
	// printf("--------\n");
	// printf("result : %s\n\n", get_next_line(fd3));
	// printf("--------\n");
	// printf("result : %s\n\n", get_next_line(fd3));
	return (0);
}
