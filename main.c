#include "get_next_line.h"

int	main(void)
{
	char	*file1 = "./data/hello.txt";
	char	*file2 = "./data/empty.txt";
	char	*file3 = "./data/1char.txt";
	char	*file4 = "./data/giant_line.txt";
	char	*file5 = "./data/nl";
	char	*file6 = "./data/read_error.txt";
	int		fd1;
	int		fd2;
	int		fd3;
	int		fd4;
	int		fd5;
	int		fd6;

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

	printf("%s\n", get_next_line(fd1));
	printf("%s\n", get_next_line(fd1));
	//printf("%s\n", get_next_line(fd2));
	// get_next_line(fd3);

	return (0);
}
