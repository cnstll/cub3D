/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:16:06 by calle             #+#    #+#             */
/*   Updated: 2021/03/17 11:45:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	play(t_data *data)
{
	int	r;

	r = 1;
	init_buffer(data);
	init_mlx_window(data);
	init_img(data);
	init_ray(data);
	if (init_textures(data) == -1)
		r = -10;
	init_map(data);
	init_inputs(data);
	if (r == 1)
	{
		render_next_frame(data);
		mlx_hook(data->win, 2, 1L << 0, &key_press, data);
		mlx_hook(data->win, 3, 1L << 1, &key_release, data);
		mlx_hook(data->win, 33, 1L << 17, &mlx_loop_end, data->mlx);
		mlx_loop_hook(data->mlx, &handle_player_move, data);
		mlx_loop(data->mlx);
	}
	free_and_destroy_play(data);
	return (r);
}

int	save(t_data *data)
{
	int r;

	r = 1;
	init_buffer(data);
	init_ray(data);
	if (init_textures(data) == -1)
		r = -10;
	init_map(data);
	if (r == 1)
	{
		cast_img(data, data->ray);
		copy_buffer_to_bimg(data, data->buffer);
	}
	free_and_destroy_save(data);
	return (r);
}

int	extract_config_elements(t_data *data, char *file_path)
{
	char	*tmp;
	char	**param;
	int		r;

	if (!file_path)
		return (-8);
	tmp = file_to_str(file_path);
	if (!tmp || check_filepath(file_path) < 1)
		return (-8);
	param = ft_lite_split(tmp, '\n');
	free(tmp);
	r = parsing_parameters(param, data->config);
	if (r >= 0)
		r = parsing_map(param, data, r);
	free_2d_string(param);
	return (r);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		r;

	data = malloc(sizeof(t_data));
	init_config(data);
	if (argc == 2)
	{
		r = extract_config_elements(data, argv[1]);
		if (r >= 0)
			r = play(data);
	}
	else if (argc == 3)
	{
		if ((data->save = ft_strncmp(argv[2], "--save", 7)) != 0)
			r = -9;
		if (r >= 0)
			r = extract_config_elements(data, argv[1]);
		if (r >= 0 && data->save == 0)
			r = save(data);
	}
	else
		r = -9;
	error_handler(r);
	destroy_config(data, data->config);
	return (1);
}
