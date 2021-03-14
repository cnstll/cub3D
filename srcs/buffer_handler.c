/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:07:21 by calle             #+#    #+#             */
/*   Updated: 2021/03/14 15:10:09 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	draw_buffer(int **buffer, t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->screen_ht)
	{
		x = 0;
		while (x < data->screen_wd)
		{
			data->img->addr[x + y * data->screen_wd] = buffer[y][x];
			x++;
		}
		y++;
	}
	return (1);
}

int	clear_buffer(int **buffer, t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->screen_ht)
	{
		x = 0;
		while (x < data->screen_wd)
		{
			buffer[y][x] = 0;
			x++;
		}
		y++;
	}
	return (1);
}
