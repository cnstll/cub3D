#include "../includes/cube.h"

int play(t_data *data)
{
	init_buffer(data);
	init_mlx_window(data);
	//init_img(data);
	init_ray(data);
	init_textures(data);
	init_map(data);
	init_inputs(data);
	init_img(data);
	cast_img(data, data->ray);
	draw_buffer(data->buffer, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	clear_buffer(data->buffer, data);
	mlx_hook(data->win, 2, 1L<<0, &key_press, data);
	mlx_hook(data->win, 3, 1L<<1, &key_release, data);
	mlx_hook(data->win, 33, 1L << 17, &mlx_loop_end, data->mlx);
	mlx_loop_hook(data->mlx, &handle_player_move, data);	
	mlx_loop(data->mlx);
	free_and_destroy_play(data);
	return (1);
}

int	save(t_data *data)
{
	
	init_buffer(data);
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (-1);
	init_ray(data);
	init_textures(data);
	init_map(data);
	cast_img(data, data->ray);
	copy_buffer_to_bimg(data, data->buffer);
	free_and_destroy_save(data);
	return (1);
}
