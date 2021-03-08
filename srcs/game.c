#include "../includes/cube.h"

int play(t_data *data)
{
	init_buffer(data);
	init_mlx_window(data);
	init_img(data);
	init_ray(data);
	init_textures(data);
	init_map(data);
	init_inputs(data);
	render_next_frame(data);
	mlx_hook(data->win, 2, 1L<<0, &key_press, data);
	mlx_hook(data->win, 3, 1L<<1, &key_release, data);
//	mlx_hook(data->win, 33, 1L<<17, &clic_to_close, data);
	mlx_loop_hook(data->mlx, &handle_player_move, data);
	mlx_loop(data->mlx);
	mlx_destroy_display(data->mlx);
	free_and_destroy_play(data);
	return (1);
}

int	save(t_data *data)
{
	
	init_buffer(data);
	init_ray(data);
	init_textures(data);
	init_map(data);
	cast_img(data, data->ray);
	copy_buffer(data, data->buffer);
	free_and_destroy_save(data);
}
