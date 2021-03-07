#include "../includes/cube.h"

void	look_left(t_ray *ray)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = ray->dir_x;
	ray->dir_x = ray->dir_x * cos(ray->rs) - ray->dir_y * sin(ray->rs);
	ray->dir_y = old_dir_x * sin(ray->rs) + ray->dir_y * cos(-ray->rs);
	old_plane_x = ray->plane_x;
	ray->plane_x = ray->plane_x * cos(ray->rs) - ray->plane_y * sin(ray->rs);
	ray->plane_y = old_plane_x * sin(ray->rs) + ray->plane_y * cos(ray->rs);
}

void	look_right(t_ray *ray)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = ray->dir_x;
	ray->dir_x = ray->dir_x * cos(-ray->rs) - ray->dir_y * sin(-ray->rs);
	ray->dir_y = old_dir_x * sin(-ray->rs) + ray->dir_y * cos(-ray->rs);
	old_plane_x = ray->plane_x;
	ray->plane_x = ray->plane_x * cos(-ray->rs) - ray->plane_y * sin(-ray->rs);
	ray->plane_y = old_plane_x * sin(-ray->rs) + ray->plane_y * cos(-ray->rs);
}
