#include "../includes/cube.h"

void	init_player_dir(t_config *config, double rot)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = config->init_dir_x;
	config->init_dir_x = 
		config->init_dir_x * cos(rot) - config->init_dir_y * sin(rot);
	config->init_dir_y = 
		old_dir_x * sin(rot) + config->init_dir_y * cos(-rot);
	old_plane_x = config->init_plane_x;
	config->init_plane_x = 
		config->init_plane_x * cos(rot) - config->init_plane_y * sin(rot);
	config->init_plane_y = 
		old_plane_x * sin(rot) + config->init_plane_y * cos(rot);

}

void	init_player(char dir, int x, int y, t_config *config)
{
	config->init_pos_x = x;
	config->init_pos_y = y;

	if (dir == 'N')
		;
	else if (dir == 'S')
	{
		init_player_dir(config, M_PI);
	}
	else if (dir == 'W')
	{
		init_player_dir(config, M_PI/2);
	}
	else
	{
		init_player_dir(config, 3 * M_PI/2);
	}
}

void init_config(t_data *data)
{
	data->config = malloc(sizeof(t_config));
	data->config->res_x = 0;
	data->config->res_y = 0;
	data->config->tx_no = "";
	data->config->tx_so = "";
	data->config->tx_ea = "";
	data->config->tx_we = "";
	data->config->tx_sprite = "";
	data->config->f_color = 0;
	data->config->c_color = 0;
	data->config->f_saved = 0;
	data->config->c_saved = 0;
	data->config->count_param = 0;
	data->config->init_dir_x = -1;
	data->config->init_dir_y = 0;
	data->config->init_plane_x = 0;
	data->config->init_plane_y = 0.66;
	data->config->init_pos_x = 0;
	data->config->init_pos_y = 0;
}
