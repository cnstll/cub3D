/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:27:47 by calle             #+#    #+#             */
/*   Updated: 2021/03/14 15:29:02 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static int	load_textures(t_data *data, t_img **textures)
{
	int x;

	textures[0]->file_paths = ft_strdup(data->config->tx_no);
	textures[1]->file_paths = ft_strdup(data->config->tx_so);
	textures[2]->file_paths = ft_strdup(data->config->tx_we);
	textures[3]->file_paths = ft_strdup(data->config->tx_ea);
	textures[4]->file_paths = ft_strdup(data->config->tx_sprite);
	x = 0;
	while (x < 5)
	{
		textures[x]->img = mlx_xpm_file_to_image(
				data->mlx, textures[x]->file_paths,
				&textures[x]->width, &textures[x]->height);
		if (!textures[x]->img)
			return (-1);
		textures[x]->addr = (int *)mlx_get_data_addr(
				textures[x]->img, &textures[x]->bpp,
				&textures[x]->line_len, &textures[x]->endian);
		x++;
	}
	return (1);
}

int			init_textures(t_data *data)
{
	int x;
	int r;

	x = 0;
	r = 1;
	data->textures = malloc(sizeof(t_img *) * 5);
	while (x < 5)
	{
		data->textures[x] = malloc(sizeof(t_img));
		x++;
	}
	r = load_textures(data, data->textures);
	return (r);
}
