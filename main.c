#include "get_next_line.h"

int	main(void)
{
	char	*file1 = "hello.txt";
	char	*file2 = "empty.txt";
	char	*file3 = "1char.txt";
	char	*file4 = "giant_line.txt";
	char	*file5 = "nl";
	char	*file6 = "read_error.txt";
	int		fd1;
	int		fd2;
	int		fd3;
	int		fd4;
	int		fd5;
	int		fd6;
	char	*save;
	int		i = 0;

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
	fd5 = open(file5, O_RDONLY);
	if (fd5 == -1)
		return (0);
	fd6 = open(file6, O_RDONLY);
	if (fd6 == -1)
		return (0);

	printf("--------\n");
	// printf("fd : 1 result : %s|\n\n", get_next_line(fd5));
	// printf("fd : 1 result : %s|\n\n", get_next_line(fd5));

	while (i < 2)
	{
		save = get_next_line(fd3);
		printf("i : %d result : %s|\n", i, save);
		free(save);
		i++;
	}

	// close(fd6);
	// fd6 = open(file6, O_RDONLY);
	// if (fd6 == -1)
	// 	return (0);
	// save = get_next_line(fd6);
	// printf("fd : 6 result : %s|\n\n", save);
	// free(save);
	// printf("fd : 1 result : %s|\n\n", get_next_line(fd1));
	// printf("fd : 1 result : %s|\n\n", get_next_line(fd1));
	// printf("result : %s\n\n\n\n", get_next_line(fd1));

	// printf("fd : 3 result : %s|\n\n", get_next_line(fd3));
	// // printf("fd : 4 result : %s\n\n", get_next_line(fd4));
	// // printf("fd : 4 result : %s\n\n", get_next_line(fd4));
	// printf("fd : 1 result : %s|\n\n", get_next_line(fd1));
	// printf("fd : 1 result : %s|\n\n", get_next_line(fd1));
	// printf("result : %s\n\n", get_next_line(fd1));

	// printf("result : %s\n\n", get_next_line(fd3));
	// printf("result : %s\n\n", get_next_line(fd3));

	// printf("--------\n");
	// printf("result : %s\n\n", get_next_line(fd3));
	return (0);
}
