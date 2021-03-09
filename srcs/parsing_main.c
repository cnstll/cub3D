#include "../includes/cube.h"

static int	map_pre_parsing(char **map, int start)
{
	int i;
	int j;
	int num_of_init_pos;

	i = start;
	num_of_init_pos = 0;
	if (!map)
		return (-1);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (c_in_s(map[i][j], " 012NSEW") == 0)
				return (-2);
			if (c_in_s(map[i][j], "NSEW") == 1)
				num_of_init_pos++;
			j++;
		}
		i++;
	}
	if (num_of_init_pos > 1)
		return (-2);
	if (num_of_init_pos == 0)
		return (-7);
	return (1);
}

static void	str_to_array(char **src, int **dest, t_data *data, int s)
{
	int i;
	int j;
	int	max_height;
	int	max_width;

	i = 0;
	max_height = data->world_ht;
	max_width = data->world_wd;
	while (i < max_height)
	{
		j = 0;
		while (j < max_width)
		{
			if (src[i + s][j] && c_in_s(src[i + s][j], "012") == 1)
				dest[i][j] = src[i + s][j] - '0';
			else if (src[i + s][j] && c_in_s(src[i + s][j], "NSWE") == 1)
			{
				init_player(src[i + s][j], i, j, data->config);
				dest[i][j] = 0;
			}
			else
				dest[i][j] = 1;
			j++;
		}
		i++;
	}
}

int			parsing_parameters(char **line, t_config *config)
{
	int i;

	i = 0;
	if (!line[i])
		return (-4);
	while (line[i])
	{
		if (line[i][0] == '\0')
			i++;
		else if (config->count_param > 8)
			return (-5);
		else if (valid_elements_pair(line[i][0], line[i][1]) == 1)
			parse_param_line(line[i++], config);
		else if (line[i][0] != '\0' && config->count_param == 8)
			return (check_if_map(line[i], i, config));
		else
			return (check_parameters(config, -3));
	}
	return (0);
}

int			parsing_map(char **map, t_data *data, int start)
{
	int	r;

	r = 0;
	r = map_pre_parsing(map, start);
	if (r < 0)
		return (r);
	r = check_map_golden_rule(map, start);
	if (r < 0)
		return (r);
	data->world_wd = map_max_width(map, start);
	data->world_ht = map_max_height(map, start);
	data->world = malloc_2d_array(data->world, data->world_wd, data->world_ht);
	str_to_array(map, data->world, data, start);
	return (r);
}
