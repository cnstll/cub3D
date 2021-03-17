/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 17:04:48 by calle             #+#    #+#             */
/*   Updated: 2021/03/17 17:10:30 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		max = (int)(fmax(ft_strlen(map[i]), max));
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
	r = ft_strnstr((file_path + i - 4), ".cub", i);
	if (!r)
		return (-1);
	else
		return (1);
}

char			*file_to_str(char *path_file)
{
	int		fd;
	char	buf[READ_SIZE + 1];
	char	*tmp;
	int		r;

	fd = open(path_file, O_RDONLY);
	r = READ_SIZE;
	tmp = NULL;
	if (fd < 0 || check_filepath(path_file) < 0)
	{
		if (fd >= 0)
			close(fd);
		return (NULL);
	}
	while (r == READ_SIZE)
	{
		ft_bzero(buf, READ_SIZE);
		r = read(fd, buf, READ_SIZE);
		buf[READ_SIZE] = '\0';
		if (r > 0)
			tmp = ft_strjoin_free(tmp, buf);
	}
	tmp = ft_strjoin_free(tmp, "\n1\n");
	close(fd);
	return (tmp);
}
