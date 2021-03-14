/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:38:54 by calle             #+#    #+#             */
/*   Updated: 2021/03/14 16:39:14 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
