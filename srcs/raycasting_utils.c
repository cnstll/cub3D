#include "../includes/cube.h"

void    ray_initiation(t_ray *ray)
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

void	diff_analysis(t_ray *ray)
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
		if (data->world[ray->map_x][ray->map_y]
			&& data->world[ray->map_x][ray->map_y] == 1)
			ray->hit = 1;
	}
}

void	calclulate_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		ray->wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
	ray->line_h = (int)(data->screen_ht / ray->wall_dist);
	ray->start = -ray->line_h / 2 + data->screen_ht / 2;
	if(ray->start < 0)
		ray->start = 0;
	ray->end = ray->line_h / 2 + data->screen_ht / 2;
	if(ray->end >= data->screen_ht || ray->end < 0)
		ray->end = data->screen_ht - 1;
	if (ray->side == 0)
		ray->wall_hit = ray->pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		ray->wall_hit = ray->pos_x + ray->wall_dist * ray->ray_dir_x;
	ray->wall_hit -= floor((ray->wall_hit));
}

void	calculate_textures(t_ray *ray, t_img **textures, *int stripes)
{
	int	lines;
	int	c;

	if(ray->side == 0 && ray->ray_dir_x > 0)
		ray->tx_x = ray->tx_wd - ray->tx_x - 1;
	if(ray->side == 1 && ray->ray_dir_y < 0)
		ray->tx_x = ray->tx_wd - ray->tx_x - 1;
	ray->step = 1.0 * ray->tx_ht / ray->line_height;
	ray->tx_pos = (ray->start - data->screen_ht / 2 + (ray->line_h / 2))
		* ray->step;
	lines = ray->start;
	while (lines < ray->end)
	{
		ray->tx_y = (int)(ray->tx_pos) & (textures[0]->height - 1);
		ray->tx_pos += ray->step;
		if (ray->side == 0 && ray->ray_dir_x < 0)
			c = textures[0]->addr[textures[0]->width * ray->tx_y + ray->tx_x];
		else if (ray->side == 0 && ray->ray_dir_x >= 0)
			c = textures[1]->addr[textures[1]->width * ray->tx_y + ray->tx_x];
		else if (ray->side == 1 && ray->ray_dir_y < 0)
			c = textures[2]->addr[textures[2]->width * ray->tx_y + ray->tx_x];
		else
			c = textures[3]->addr[textures[3]->width * ray->tx_y + ray->tx_x];
		data->buffer[lines++][stripes] = c;
	}
}
