/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:11:22 by calle             #+#    #+#             */
/*   Updated: 2021/03/14 15:11:26 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	destroy_config(t_data *data, t_config *config)
{
	if (config->tx_no[0] != '\0')
		free(config->tx_no);
	if (config->tx_so[0] != '\0')
		free(config->tx_so);
	if (config->tx_ea[0] != '\0')
		free(config->tx_ea);
	if (config->tx_we[0] != '\0')
		free(config->tx_we);
	if (config->tx_sprite[0] != '\0')
		free(config->tx_sprite);
	free(config);
	free(data);
}

void	destroy_sprites(t_data *data)
{
	free(data->sprite->buffer);
	free(data->sprite->distance);
	free(data->sprite->sp);
	free(data->sprite);
}

void	destroy_textures(t_data *data)
{
	int x;

	x = 0;
	while (x < 5)
	{
		if (!data->textures[x]->img)
			break ;
		else
			mlx_destroy_image(data->mlx, data->textures[x]->img);
		x++;
	}
	x = 0;
	while (x < 5)
	{
		free(data->textures[x]->file_paths);
		free(data->textures[x]);
		x++;
	}
	free(data->textures);
}

void	free_and_destroy_play(t_data *data)
{
	free(data->ray);
	mlx_destroy_image(data->mlx, data->img->img);
	free(data->img);
	free(data->inputs);
	free_2d_array(data->buffer, data->screen_ht);
	free_2d_array(data->world, data->world_ht);
	destroy_sprites(data);
	destroy_textures(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	free_and_destroy_save(t_data *data)
{
	free(data->ray);
	free_2d_array(data->buffer, data->screen_ht);
	free_2d_array(data->world, data->world_ht);
	destroy_sprites(data);
	destroy_textures(data);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}
