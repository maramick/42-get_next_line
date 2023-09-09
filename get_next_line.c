#include "./get_next_line.h"

char	*get_next_line(int fd)
{

}

int	main(void)
{
	char*	fileName = "files/30_with_nl";
	int		fd;

	fd = open(fileName, O_RDONLY);
	if (fd == -1)
		return (0);
	printf("%s", get_next_line(fd));
}
