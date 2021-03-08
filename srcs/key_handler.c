#include "../includes/cube.h"

int		key_release(int keysym, t_data *data)
{
	if (keysym == XK_w)
		data->inputs->key_w = 0;
	if (keysym == XK_s)
		data->inputs->key_s = 0;
	if (keysym == XK_a)
		data->inputs->key_a = 0;
	if (keysym == XK_d)
		data->inputs->key_d = 0;
	if (keysym == XK_Left)
		data->inputs->key_left = 0;
	if (keysym == XK_Right)
		data->inputs->key_right = 0;
	return (1);
}

int		key_press(int keysym, t_data *data)
{
	if (keysym == XK_w)
		data->inputs->key_w = 1;
	if (keysym == XK_s)
		data->inputs->key_s = 1;
	if (keysym == XK_a)
		data->inputs->key_a = 1;
	if (keysym == XK_d)
		data->inputs->key_d = 1;
	if (keysym == XK_Left)
		data->inputs->key_left = 1;
	if (keysym == XK_Right)
		data->inputs->key_right = 1;
	if (keysym == XK_Escape && data->win)
	{
		data->inputs->key_esc = 1;
		free_2d_array(data->buffer, data->screen_ht);
		mlx_destroy_window(data->mlx, data->win);
		mlx_loop_end(data->mlx);
	}
	return (1);
}

int		any_key_pressed(t_input *inputs)
{
	int	ret;

	if (inputs->key_w == 1)
		ret = 1;
	else if (inputs->key_s == 1)
		ret = 1;
	else if (inputs->key_a == 1)
		ret = 1;
	else if (inputs->key_d == 1)
		ret = 1;
	else if (inputs->key_left == 1)
		ret = 1;
	else if (inputs->key_right == 1)
		ret = 1;
	else
		ret = 0;
	return (ret);
}

int		handle_player_move(t_data *data)
{
	int	esc;

	esc = data->inputs->key_esc;
	if (data->inputs->key_w == 1 && esc < 1)
		move_up(data->ray, data->world);
	if (data->inputs->key_s == 1 && esc < 1)
		move_down(data->ray, data->world);
	if (data->inputs->key_a == 1 && esc < 1)
		move_left(data->ray, data->world);
	if (data->inputs->key_d == 1 && esc < 1)
		move_right(data->ray, data->world);
	if (data->inputs->key_left == 1 && esc < 1)
		look_left(data->ray);
	if (data->inputs->key_right == 1)
		look_right(data->ray);
	if (any_key_pressed(data->inputs) == 1 && esc < 1)
		render_next_frame(data);
	return (1);
}

int		clic_to_close(int clic, t_data *data)
{
	printf("%d\n", clic);
	if (clic == 1634464352)
	{
		printf("closing\n");
		data->inputs->key_esc = 1;
		free_2d_array(data->buffer, data->screen_ht);
		mlx_destroy_window(data->mlx, data->win);
		mlx_loop_end(data->mlx);
	}
	return(1);
}
