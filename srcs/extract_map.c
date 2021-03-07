#include "./includes/cube.h"

void	error_handler(int error)
{
	if (error < 0)
		printf("Error\n");
	if (error == -1)
		printf("Something went wrong with the configuration/map file\n");
	else if (error == -2)
		printf("Invalid character in map\n");
	else if (error == -3)
		printf("Invalid configuration\n");
	else if (error == -4)
		printf("Empty configuration file\n");
	else if (error == -5)
		printf("Too many configuration parameters\n");
	else if (error == -6)
		printf("Configuration parameter missing or invalid\n");
	else if (error == -7)
		printf("Invalid map\n");
	else if (error == -8)
		printf("No input file\n");
	else
		printf("Configuration ok\n");
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

void	destroy_config(t_config *config)
{
	if (config->tx_no[0] != '\0')
		free(config->tx_no);
	if (config->tx_so[0] != '\0')
		free(config->tx_so);
	if (config->tx_ea[0] != '\0')
		free(config->tx_ea);
	if (config->tx_we[0] != '\0')
		free(config->tx_we);
	if (config->tx_sprite[0] != '\0')
		free(config->tx_sprite);
	free(config);
}

int count_c_in_s(char c, char *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s && s[i])
		if (s[i++] == c)
			count++;
	return (count);
}

void	init_player_dir(t_config *config, double rot)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = config->init_dir_x;
	config->init_dir_x = config->init_dir_x * cos(rot) - config->init_dir_y * sin(rot);
	config->init_dir_y = old_dir_x * sin(rot) + config->init_dir_y * cos(-rot);
	old_plane_x = config->init_plane_x;
	config->init_plane_x = config->init_plane_x * cos(rot) - config->init_plane_y * sin(rot);
	config->init_plane_y = old_plane_x * sin(rot) + config->init_plane_y * cos(rot);

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

void print_2d_str(char **str, int start)
{
	int i;
	int j;

	i = start;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			printf("%c", str[i][j]);
			if (!str[i][j + 1])
				printf("\n");
			j++;
		}
		i++;
	}
}

char *file_to_str(char *path_file)
{
	int fd;
	char buf[READ_SIZE + 1];
	char *tmp;
	int r;

	fd = 0;
	fd = open(path_file, O_RDONLY);
	r = READ_SIZE;
	tmp = NULL;
	if (fd < 0)
		return (NULL);
	while (r == READ_SIZE)
	{
		ft_bzero(buf, READ_SIZE);
		r = read(fd, buf, READ_SIZE);
		buf[READ_SIZE] = '\0';
		if (r > 0)
			tmp = ft_strjoin_free(tmp, buf);
	}
	close(fd);
	return (tmp);
}

int		map_max_width(char **map, int start)
{
	int	max;
	int	i;

	max = 0;
	i = start;
	while (map[i])
	{
		max = (int)(fmax(ft_strlen(map[i]),max));
		i++;
	}
	return (max);
}

int	map_max_height(char **map, int start)
{
	int	max;

	max = start;
	while (map[max])
		max++;
	max = max - start - 1;
	return (max);
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

int valid_elements_pair(char e1, char e2)
{
	if (c_in_s(e1, "RFC") > 0 && e2 == ' ')
		return (1);
	else if (e1 == 'S' && (e2 == ' ' || e2 == 'O'))
		return (1);
	else if (e1 == 'E' && e2 == 'A')
		return (1);
	else if (e1 == 'W' && e2 == 'E')
		return (1);
	else if (e1 == 'N' && e2 == 'O')
		return (1);
	else
		return (-1);
}

int	check_path(char *p, int start)
{
	int j;

	j = start;
	while (p[j])
	{
		if (ft_isalpha(p[j]) == 1 || p[j] == '_' || p[j] == '/' || p[j] == '.')
			j++;
		else
			return (-1);
	}
	return (1);
}

int	copy_path(char *p, t_config *config, int start)
{
	config->count_param++;
	if (p[0] == 'E' && p[1] == 'A' && !*config->tx_ea)
		config->tx_ea = ft_strdup(p + start);
	else if (p[0] == 'S' && p[1] == 'O' && !*config->tx_so)
		config->tx_so = ft_strdup(p + start);
	else if (p[0] == 'W' && p[1] == 'E' && !*config->tx_we)
		config->tx_we = ft_strdup(p + start);
	else if (p[0] == 'N' && p[1] == 'O' && !*config->tx_no)
		config->tx_no = ft_strdup(p + start);
	else if (p[0] == 'S' && p[1] == ' ' && !*config->tx_sprite)
		config->tx_sprite = ft_strdup(p + start);
	return (0);
}

int	check_res(char *p, int start)
{
	int j;
	int space;

	j = start;
	space = 0;
	if (p[0] != 'R')
		return (-1);
	while (p[j])
	{
		if (ft_isdigit(p[j]) == 1 && space < 2)
			j++;
		else if (p[j] == ' ' && space == 0)
		{
			space++;
			j++;
		}
		else
			return (-1);
	}
	return (1);
}

int	copy_res(char *p, t_config *config, int start)
{
	int		j;
	char	*tmp;

	j = start;
	tmp = ft_strdup("");
	while (ft_isdigit(p[j]) == 1)
	{
		tmp = ft_str_append(tmp, p[j]);
		j++;
	}
	config->res_x = ft_lite_atoi(tmp);
	free(tmp);
	tmp = ft_strdup("");
	while (ft_isdigit(p[++j]) == 1)
		tmp = ft_str_append(tmp, p[j]);
	config->res_y = ft_lite_atoi(tmp);
	free(tmp);
	config->count_param++;
	return (0);
}

unsigned long rgb_to_hex(int r, int g, int b)
{
    unsigned int	u;

	u = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (u);
}

int	check_color(char *p, int start)
{
	int j;
	int comma;

	j = start;
	comma = 0;
	if (p[0] != 'C' && p[0] != 'F')
		return (-1);
	while (p[j])
	{
		if (ft_isdigit(p[j]) == 1 && comma < 3)
			j++;
		else if (p[j++] == ',' && comma < 2)
			comma++;
		else
			return (-1);
	}
	return (1);
}

int	copy_color(char *p, t_config *config, int start)
{
	int r;
	int g;
	int b;
	char **tmp;

	tmp = ft_lite_split(p + start, ',');
	r = ft_lite_atoi(tmp[0]);
	g = ft_lite_atoi(tmp[1]);
	b = ft_lite_atoi(tmp[2]);
	free_2d_string(tmp);
	if (p[0] == 'F')
		config->f_color = rgb_to_hex(r,g,b);
	if (p[0] == 'C')
		config->c_color = rgb_to_hex(r,g,b);
	if (p[0] == 'F')
		config->f_saved++;
	if (p[0] == 'C')
		config->c_saved++;
	config->count_param++;
	return (0);
}

void	parse_param_line(char *p, t_config *config)
{
	int i;
	int done;

	i = 2;
	done = 1;
	while (p[i] && done == 1)
	{
		if (p[i] == ' ')
			i++;
		else if (p[i] == '.' && p[i + 1] == '/' && check_path(p, i + 2) == 1)
			done = copy_path(p, config, i);
		else if(p[0] == 'R' && ft_isdigit(p[i]) && check_res(p, i) == 1)
			done = copy_res(p, config, i);
		else if(p[0] == 'C' && ft_isdigit(p[i]) && check_color(p, i) == 1)
			done = copy_color(p, config, i);
		else if(p[0] == 'F' && ft_isdigit(p[i]) && check_color(p, i) == 1)
			done = copy_color(p, config, i);
		else
			return ;
	}
}

int	check_parameters(t_config *config, int ret)
{
	if (!*config->tx_ea)
		ret = -6;
	else if (!*config->tx_so)
		ret = -6;
	else if (!*config->tx_we)
		ret = -6;
	else if (!*config->tx_no)
		ret = -6;
	else if (!*config->tx_sprite)
		ret = -6;
	else if (config->res_x < 1)
		ret = -6;
	else if (config->res_y < 1)
		ret = -6;
	else if (config->c_saved < 1)
		ret = -6;
	else if (config->f_saved < 1)
		ret = -6;
	return (ret);
}

int check_if_map(char *line, int num_line, t_config *config)
{
	int i;

	i = check_parameters(config, 0);
	if (i < 0)
		return (i);
	else
		i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (-7);
		i++;
	}
	return (num_line);
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

	if (argc > 1 && argc < 3 && ft_strncmp(argv[1], "--save", 7) != 0)
	{
		r = 0;
		data = malloc(sizeof(t_data));
		init_config(data);
		r = extract_config_elements(data, argv[1]);
		data->save = ft_strncmp(argv[1], "--save", 7);
		if (data->save)
			data->save = 1;
		if (r >= 0)
			set_configuration(data);
		destroy_config(data->config);
	}
	else
		error_handler(-8);
	return (1);
}
