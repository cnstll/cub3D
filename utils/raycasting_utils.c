/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:45:02 by calle             #+#    #+#             */
/*   Updated: 2021/03/14 16:47:37 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	ray_initiation(t_ray *ray, int stripes, int max_stripes)
{
	ray->camera_x = 2 * stripes / (double)(max_stripes) - 1;
	ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
	ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
	ray->map_x = (int)(ray->pos_x);
	ray->map_y = (int)(ray->pos_y);
	if (ray->ray_dir_y == 0)
		ray->delta_dx = 0;
	else if (ray->ray_dir_x == 1)
		ray->delta_dx = 1;
	else
		ray->delta_dx = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_x == 0)
		ray->delta_dy = 0;
	else if (ray->ray_dir_y == 1)
		ray->delta_dy = 1;
	else
		ray->delta_dy = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	ray_step_and_side(t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dx = (ray->pos_x - ray->map_x) * ray->delta_dx;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dx = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dx;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dy = (ray->pos_y - ray->map_y) * ray->delta_dy;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dy = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dy;
	}
}

void	diff_analysis(t_ray *ray, int **world)
{
	while (ray->hit == 0)
	{
		if (ray->side_dx < ray->side_dy)
		{
			ray->side_dx += ray->delta_dx;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dy += ray->delta_dy;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (world[ray->map_x][ray->map_y]
			&& world[ray->map_x][ray->map_y] == 1)
			ray->hit = 1;
	}
}

void	calculate_wall_dist(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		ray->wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
	ray->line_h = (int)(data->screen_ht / ray->wall_dist);
	ray->start = -ray->line_h / 2 + data->screen_ht / 2;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->line_h / 2 + data->screen_ht / 2;
	if (ray->end >= data->screen_ht || ray->end < 0)
		ray->end = data->screen_ht - 1;
	if (ray->side == 0)
		ray->wall_hit = ray->pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		ray->wall_hit = ray->pos_x + ray->wall_dist * ray->ray_dir_x;
	ray->wall_hit -= floor((ray->wall_hit));
}

void	calculate_textures(t_data *data, t_ray *ray, t_img **textures, int s)
{
	int	lines;
	int	c;
	int tx_n;

	if (ray->side == 0 && ray->ray_dir_x < 0)
		tx_n = 0;
	else if (ray->side == 0 && ray->ray_dir_x > 0)
		tx_n = 1;
	else if (ray->side == 1 && ray->ray_dir_y < 0)
		tx_n = 2;
	else
		tx_n = 3;
	ray->tx_x = (int)(ray->wall_hit * (double)(textures[tx_n]->width));
	ray->tx_x = textures[tx_n]->width - ray->tx_x - 1;
	ray->step = 1.0 * textures[tx_n]->height / ray->line_h;
	ray->tx_pos = (ray->start - data->screen_ht / 2 + (ray->line_h / 2))
		* ray->step;
	lines = ray->start;
	while (lines < ray->end)
	{
		ray->tx_y = (int)(ray->tx_pos) & (textures[tx_n]->height - 1);
		ray->tx_pos += ray->step;
		c = textures[tx_n]->addr[textures[tx_n]->width * ray->tx_y + ray->tx_x];
		data->buffer[lines++][s] = c;
	}
}
