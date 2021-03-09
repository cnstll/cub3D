#include "../includes/cube.h"

void str_to_array(char **src, int **dest, t_data *data, int start)
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
			if (src[i + start][j] && c_in_s(src[i + start][j], "012") == 1)
				dest[i][j] = src[i + start][j] - '0';
			else if (src[i + start][j] && c_in_s(src[i + start][j], "NSWE") == 1)
			{
				init_player(src[i + start][j], i, j, data->config);
				dest[i][j] = 0;
			}
			else
				dest[i][j] = 1;
			j++;
		}
		i++;
	}
}

void print_array(int **array, int max_width, int max_height)
{
	int i;
	int j;

	i = 0;
	while (i < max_height)
	{
		j = 0;
		while (j < max_width)
		{
			printf("%d", array[i][j]);
			if (j == max_width - 1)
				printf("\n");
			j++;
		}
		i++;
	}
}

int		map_pre_parsing(char **map, int start)
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

int	parsing_parameters(char **line, t_config *config)
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

int	apply_golden_rule(char **map, int i, int j)
{
	if (c_in_s(map[i - 1][j - 1], " 1") == 0)
		return (-7);
	if (c_in_s(map[i - 1][j], " 1") == 0)
		return (-7);
	if (c_in_s(map[i - 1][j + 1], " 1") == 0)
		return (-7);
	if (c_in_s(map[i][j - 1], " 1") == 0)
		return (-7);
	if (c_in_s(map[i][j + 1], " 1") == 0)
		return (-7);
	if (c_in_s(map[i + 1][j - 1], " 1") == 0)
		return (-7);
	if (c_in_s(map[i + 1][j], " 1") == 0)
		return (-7);
	if (c_in_s(map[i + 1][j + 1], " 1") == 0)
		return (-7);
	//printf("check golden rule\n");
	//printf("i - %d <> j - %d\n", i - 9, j);
	return (1);
}

int	check_n_w(char **map, int i, int j, int start)
{
	if (i - start == 0 && map[i][j] == ' ')
	{
		if (map[i + 1][j - 1] && !c_in_s(map[i + 1][j - 1], " 1"))
			return (-7);
		if (map[i + 1][j] && !c_in_s(map[i + 1][j], " 1"))
			return (-7);
		if (map[i + 1][j + 1] && !c_in_s(map[i + 1][j + 1], " 1"))
			return (-7);
	}
	else if (j == 0 && map[i][j] == ' ')
	{
		if (map[i - 1][j + 1] && !c_in_s(map[i - 1][j + 1], " 1"))
			return (-7);
		if (map[i][j + 1] && !c_in_s(map[i][j + 1], " 1"))
			return (-7);
		if (map[i + 1][j + 1] && !c_in_s(map[i + 1][j + 1], " 1"))
			return (-7);
	}
	return (1);
}

int	check_borders(char **map, int i, int j, int start)
{
	//printf("check border\n");
	//printf("i - %d <> j - %d\n", i - 9, j);
	//printf("map = '%c'\n", map[i][j]);
	if (!c_in_s(map[i][j], " 1"))
		return (-7);
	else if ((j == 0 || i - start == 0) && map[i][j] == ' ')
		return (check_n_w(map, i, j, start));
	else if (!map[i][j + 1] && map[i][j] == ' ')
	{
		if (map[i - 1][j - 1] && !c_in_s(map[i - 1][j - 1], " 1"))
			return (-7);
		if (map[i][j - 1] && !c_in_s(map[i][j - 1], " 1"))
			return (-7);
		if (map[i + 1][j - 1] && !c_in_s(map[i + 1][j - 1], " 1"))
			return (-7);
	}
	else if (!map[i + 1][j] && map[i][j] == ' ')
	{
		if (map[i - 1][j - 1] && !c_in_s(map[i - 1][j - 1], " 1"))
			return (-7);
		if (map[i - 1][j] && !c_in_s(map[i - 1][j], " 1"))
			return (-7);
		if (map[i - 1][j + 1] && !c_in_s(map[i - 1][j + 1], " 1"))
			return (-7);
	}
	return (1);
}

int	is_border(char **map, int i, int j, int start)
{
	if (j == 0 || i - start == 0)
		return (-1);
	if (!map[i - 1][j - 1] || !map[i - 1][j + 1])
		return (-1);
	if (!map[i + 1][j - 1] || !map[i + 1][j + 1])
		return (-1);
	if (!map[i][j - 1] || !map[i][j + 1])
		return (-1);
	if (!map[i - 1][j] || !map[i + 1][j])
		return (-1);
	return (1);
}

int check_map_golden_rule(char **map, int start)
{
	int	r;
	int	j;
	int	i;

	i = start;
	r = 1;
	while (map[i] && r == 1)
	{
		j = 0;
		while (map[i][j] && r == 1)
		{
			if (is_border(map, i, j, start) > 0 && map[i][j] == ' ')
				r = apply_golden_rule(map, i, j);
			else if (is_border(map, i, j, start) < 0)
				r = check_borders(map, i, j, start);
			j++;
		}
		i++;
	}
	return (r);
}

int	parsing_map(char **map, t_data *data, int start)
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
	print_array(data->world, data->world_wd, data->world_ht);
	printf("\nmap_parsing output - %d\n", r);
	return (r);
}
