#include "../includes/cube.h"

int		init_buffer(t_data *data)
{
	int size_x;
	int size_y;

	size_x = 0;
	size_y = 0;
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (-1);
	data->screen_ht = data->config->res_y;
	data->screen_wd = data->config->res_x;
	mlx_get_screen_size(data->mlx, &size_x, &size_y);
	if (!data->save && (data->screen_wd > size_x || data->screen_ht > size_y))
	{
		data->screen_wd = size_x;
		data->screen_ht = size_y;
	}
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
			data->img->img, &data->img->bpp, &data->img->line_len, &data->img->endian);
	return (1);
}

int		init_ray(t_data *data)
{
	data->ray = malloc(sizeof(t_ray));
	data->ray->pos_x = data->config->init_pos_x;
	data->ray->pos_y = data->config->init_pos_y;
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
