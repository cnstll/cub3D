/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:06:06 by calle             #+#    #+#             */
/*   Updated: 2021/03/14 15:06:40 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static int	put_ceilling(t_data *data, int stripes, int wall_top)
{
	int i;

	i = 0;
	while (i < wall_top - 1)
		data->buffer[i++][stripes] = data->config->c_color;
	return (1);
}

static int	put_floor(t_data *data, int stripes, int wall_bot)
{
	int i;

	i = wall_bot + 1;
	while (i < data->screen_ht)
		data->buffer[i++][stripes] = data->config->f_color;
	return (1);
}

int			cast_img(t_data *data, t_ray *ray)
{
	int stripes;
	int max_stripes;

	stripes = 0;
	max_stripes = data->screen_wd;
	while (stripes < max_stripes)
	{
		ray_initiation(ray, stripes, max_stripes);
		ray_step_and_side(ray);
		diff_analysis(ray, data->world);
		calculate_wall_dist(ray, data);
		calculate_textures(data, ray, data->textures, stripes);
		put_ceilling(data, stripes, ray->start);
		put_floor(data, stripes, ray->end);
		data->sprite->buffer[stripes] = ray->wall_dist;
		stripes++;
	}
	handle_sprites(data, ray, data->sprite);
	return (1);
}

int			render_next_frame(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img->img);
	free(data->img);
	init_img(data);
	cast_img(data, data->ray);
	draw_buffer(data->buffer, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	clear_buffer(data->buffer, data);
	return (1);
}
