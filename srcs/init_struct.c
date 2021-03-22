/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:24:05 by calle             #+#    #+#             */
/*   Updated: 2021/03/21 18:19:03 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int		init_buffer(t_data *data, t_config *config)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (-1);
	data->screen_wd = config->res_x;
	data->screen_ht = config->res_y;
	if (data->save == 0 && config->res_x > config->res_x_max)
		data->screen_wd = config->res_x_max;
	if (data->save == 0 && config->res_y > config->res_y_max)
		data->screen_ht = config->res_y_max;
	if (data->save != 0)
		mlx_get_screen_size(data->mlx, &config->res_x_max, &config->res_y_max);
	if (data->save != 0 && config->res_x > config->res_x_max)
		data->screen_wd = config->res_x_max;
	if (data->save != 0 && config->res_y > config->res_y_max)
		data->screen_ht = config->res_y_max;
	data->buffer = NULL;
	data->buffer =
		malloc_2d_array(data->buffer, data->screen_wd, data->screen_ht);
	if (data->buffer == NULL)
		return (-1);
	return (1);
}

int		init_mlx_window(t_data *data)
{
	data->win =
		mlx_new_window(data->mlx, data->screen_wd, data->screen_ht, "cub3D");
	if (data->win == NULL)
		return (-1);
	return (1);
}

int		init_img(t_data *data)
{
	data->img = malloc(sizeof(t_img));
	data->img->img =
		mlx_new_image(data->mlx, data->screen_wd, data->screen_ht);
	data->img->addr = (int *)mlx_get_data_addr(
			data->img->img, &data->img->bpp,
			&data->img->line_len, &data->img->endian);
	return (1);
}

int		init_ray(t_data *data)
{
	data->ray = malloc(sizeof(t_ray));
	data->ray->pos_x = data->config->init_pos_x + 0.5;
	data->ray->pos_y = data->config->init_pos_y + 0.5;
	data->ray->ms = 0.05;
	data->ray->rs = 0.04;
	data->ray->dir_x = data->config->init_dir_x;
	data->ray->dir_y = data->config->init_dir_y;
	data->ray->plane_x = data->config->init_plane_x;
	data->ray->plane_y = data->config->init_plane_y;
	data->ray->side_dx = 0;
	data->ray->side_dy = 0;
	data->ray->step_x = 0;
	data->ray->step_y = 0;
	data->ray->wall_dist = 0;
	data->ray->wall_hit = 0;
	data->ray->side = 0;
	data->ray->hit = 0;
	data->ray->step = 0;
	data->ray->line_h = 0;
	data->ray->start = 0;
	data->ray->end = 0;
	data->ray->tx_x = 0;
	data->ray->tx_y = 0;
	data->ray->tx_pos = 0;
	return (1);
}

int		init_inputs(t_data *data)
{
	data->inputs = malloc(sizeof(t_input));
	data->inputs->key_w = 0;
	data->inputs->key_s = 0;
	data->inputs->key_a = 0;
	data->inputs->key_d = 0;
	data->inputs->key_left = 0;
	data->inputs->key_right = 0;
	data->inputs->key_esc = 0;
	return (1);
}
