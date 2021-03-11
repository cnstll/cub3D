#include "../includes/cube.h"

unsigned long	rgb_to_hex(int r, int g, int b)
{
    unsigned int	u;

	u = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (u);
}

int				map_max_width(char **map, int start)
{
	int	max;
	int	i;

	max = 0;
	i = start;
	while (map[i])
	{
		max = (int)(fmax(ft_strlen(map[i]),max));
		i++;
	}
	return (max);
}

int				map_max_height(char **map, int start)
{
	int	max;

	max = start;
	while (map[max])
		max++;
	max = max - start - 1;
	return (max);
}

int				check_filepath(char *file_path)
{
	int		i;
	char	*r;

	i = 0;
	while (file_path && file_path[i])
		i++;
	r = ft_strnstr(file_path, ".cub", i);
	if (!r)
		return (-1);
	else
		return (1);
}

char			*file_to_str(char *path_file)
{
	int fd;
	char buf[READ_SIZE + 1];
	char *tmp;
	int r;

	fd = 0;
	fd = open(path_file, O_RDONLY);
	r = READ_SIZE;
	tmp = NULL;
	if (fd < 0)
		return (NULL);
	while (r == READ_SIZE)
	{
		ft_bzero(buf, READ_SIZE);
		r = read(fd, buf, READ_SIZE);
		buf[READ_SIZE] = '\0';
		if (r > 0)
			tmp = ft_strjoin_free(tmp, buf);
	}
	close(fd);
	return (tmp);
}
