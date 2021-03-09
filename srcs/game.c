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

int extract_config_elements(t_data *data, char *path_file)
{
	char	*tmp;
	char	**param;
	int		r;

	tmp = file_to_str(path_file);
	if (!tmp)
		return (-1);
	param = ft_lite_split(tmp, '\n');
	free(tmp);
	r = parsing_parameters(param, data->config);
	if (r >= 0)
		r = parsing_map(param, data, r);
	free_2d_string(param);
	error_handler(r);
	return (r);
}


int main(int argc, char *argv[])
{
	t_data	*data;
	int		r;

	if (argc > 1 && argc < 3)
	{
		r = 0;
		data = malloc(sizeof(t_data));
		init_config(data);
		data->save = ft_strncmp(argv[1], "--save", 7);
		if (data->save == 0)
			r = extract_config_elements(data, "./maps/map_full_test.cub");
		else
			r = extract_config_elements(data, argv[1]);
		if (r >= 0 && data->save != 0)
			play(data);
		if (r >= 0 && data->save == 0)
			save(data);
		destroy_config(data->config);
		free(data);
	}
	else
		error_handler(-8);
	return (1);
}
