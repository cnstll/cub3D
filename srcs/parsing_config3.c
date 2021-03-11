#include "../includes/cube.h"

int	check_texture_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd >= 0)
	{
		close(fd);
		fd = 1; 
	}
	else
		fd = 0;
	return (fd);
}
