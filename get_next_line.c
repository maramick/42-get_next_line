#include "./get_next_line.h"

size_t	ft_readline(int fd)
{
	ssize_t	bytes_read;
	char	c[1];
	int		i;

	i = 0;
	bytes_read = read(fd, c, sizeof(c));
	while (c[0] != '\n')
	{
		printf("%c", c[0]);
		bytes_read = read(fd, c, sizeof(c));
		if (bytes_read == -1)
			exit(0);
		i++;
	}
	return (i);
}

char	*get_next_line(int fd)
{
	char	*str;
	size_t	line_length;


	line_length = ft_readline(fd);
	printf("\nline_length : %zu", line_length);
	str = (char *)calloc(line_length, sizeof(char));
	while (line_length > 0)
	{
		line_length--;
	}

	return (str);
}

int	main(void)
{
	char*	fileName = "hello.txt";
	int		fd;

	fd = open(fileName, O_RDONLY);
	if (fd == -1)
		return (0);
	printf("%s", get_next_line(fd));
}
