#include "./includes/cube.h"

void	error_handler(int error)
{
	if (error < 0)
		printf("Error\n");
	if (error == -1)
		printf("Empty map!\n");
	if (error == -2)
		printf("Inappropriate character in map\n");
	if (error == -3)
		printf("Wrong game configuration\n");
}

void init_config(t_data *data)
{
	data->config = malloc(sizeof(t_config));
	data->config->resolution_x = "";
	data->config->resolution_y = "";
	data->config->tx_no = "";
	data->config->tx_so = "";
	data->config->tx_ea = "";
	data->config->tx_we = "";
	data->config->tx_sprite = "";
	data->config->f_color = "";
	data->config->c_color = "";
	data->config->count_param = 0;
}

void	destroy_config(t_config *config)
{
	if (config->resolution_x[0] != '\0')
		free(config->resolution_x);
	if (config->resolution_y[0] != '\0')
		free(config->resolution_y);
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
	if (config->f_color[0] != '\0')
		free(config->f_color);
	if (config->c_color[0] != '\0')
		free(config->c_color);
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

void str_to_array(char **src_map, int **dest_array, int max_width, int max_height)
{
	int i;
	int j;

	i = 0;
	while (i < max_height - 1)
	{
		j = 0;
		while (j < max_width)
		{
			if (src_map[i][j])
				dest_array[i][j] = src_map[i][j];
			else
				dest_array[i][j] = ' ';
			j++;
		}
		i++;
	}
}

void print_array(int **array, int max_width, int max_height)
{
	int x;
	int y;

	x = 0;
	while (x < max_height)
	{
		y = 0;
		while (y < max_width)
		{
			printf("%d", array[x][y]);
			if (y != 23)
				printf(" ");
			else
				printf("\n");
			y++;
		}
		x++;
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

int		map_max_width(char **map)
{
	int	max;
	int	i;

	max = 0;
	i = 0;
	while (map[i])
	{
		max = (int)(fmax(ft_strlen(map[i]),max));
		i++;
	}
	printf("max ln - %d\n", max);
	return (max);
}

int	map_max_height(char **map)
{
	int	max;

	max = 0;
	while (map[max])
		max++;
	printf("max height - %d\n", max);
	return (max);
}

int		map_pre_parsing(char *map)
{
	int i;

	i = 0;
	if (!map)
		return (-1);
	while (map[i])
	{
		if(c_in_s(map[i], "\t 012NSEW\n") != 1)
			return (-2);
		i++;
	}
	return (1);
}

char **ft_lite_split(char *s, char c)
{
	char **ret;
	int		j;
	int		k;
	int		n_lines;

	j = 0;
	k = 0;
	n_lines = count_c_in_s(c, s);
	ret = (char **)malloc(sizeof(char *) * (n_lines + 1));
	if (ret == NULL)
		return (NULL);
	while (j < n_lines)
	{
		ret[j] = ft_strdup_till_char(s, c, k);
		while (s[k] && s[k] != c)
			k++;
		if (s[k] == c)
			k++;
		j++;
	}
	ret[n_lines] = 0;
	return (ret);
}

int	window_resolution()
{

	return (1);
}

int valid_elements_pair(char e1, char e2)
{
	config->count_param++;
	if (c_in_s(e1, "RFC") == 1 && e2 == ' ')
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

int	check_path_file(char *p, int start)
{
	int j;

	j = start;
	while (p[j])
	{
		if (ft_isalpha(p[j]) == 1 || p[j] == '_')
			j++;
		else
			return (-1);
	}
	return (1);
}

void	copy_path_file(char *p, t_config *config, int start)
{
	if (p[0] == 'E' && p[1] == 'A')
		config->tx_ea = ft_strdup(p + start);
	else if (p[0] == 'S' && p[1] == 'O')
		config->tx_so = ft_strdup(p + start);
	else if (p[0] == 'W' && p[1] == 'E')
		config->tx_we = ft_strdup(p + start);
	else if (p[0] == 'N' && p[1] == 'O')
		config->tx_no = ft_strdup(p + start);
	else if (p[0] == 'S' && p[1] == ' ')
		config->tx_sprite = ft_strdup(p + start);
	else
		return ;
}

int	check_res(char *p, int start)
{
	int j;
	int space;

	j = start;
	space = 0;
	while (p[j])
	{
		if (ft_isdigit(p[j]) == 1 || (p[j++] == ' ' && space == 0))
			space = 1;
		else
			return (-1);
	}
	return (1);
	
}

void	copy_res(char *p, t_config *config, int start)
{
	int j;
	
	j = start;
	while (ft_isdigit(p[j]) == 1)
	{
		config->resolution_x = ft_str_append(p + start, p[j]);
		j++;
	}
	while (ft_isdigit(p[++j]) == 1)
		config->resolution_y = ft_str_append(p + start, p[j]);
}

unsigned long rgb_to_hex(int r, int g, int b)
{
    unsigned long	u;
	
	u =  ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF);
	return (u);
}

int	check_color(char *p, int start)
{
	int j;
	int space;

	j = start;
	comma = 0;
	while (p[j])
	{
		if (ft_isdigit(p[j]) == 1 || (p[j++] == ',' && comma < 2))
			comma++;
		else
			return (-1);
	}
	return (1);
	
}

void	copy_color(char *p, t_config *config, int start)
{
	int	r;
	int	g;
	int	b;
	char **tmp;

	tmp = ft_lite_split(p, ',');
	r = ft_lite_atoi(p[0]);
	g = ft_lite_atoi(p[1]);
	b = ft_lite_atoi(p[2]);
	if (p[0] = 'F')		
		config->f_color = rgb_to_hex(r, g, b);
	if (p[0] = 'C')		
		config->c_color = rgb_to_hex(r, g, b);
}

int parse_param_line(char *p, t_data *data, t_config *config)
{
	int i;
	int done;

	i = 2;
	done == 1;
	while (p[i] && done == 1)
	{
		if (p[i] = ' ')
			i++;
		else if (p[i] = '.' && p[i + 1] = '/')
		{
			if (check_path_file(p, i + 2) == 1)
			{
				copy_path_file(p, i);
				done = 0;
			}
			else
				return (error_handler(-3));
		}
		else if(ft_isdigit(p[i]) && check_res(p, i) == 1 && p[0] = 'R')
			copy_res(p, i);
		else if(ft_isdigit(p[i]) && check_color(p, i) == 1)
			copy_color(p, i);
		else
			return (error_handler(-3));
	}
}

// 8 Elements to parse before map
int	parsing_parameters(char **param, t_data *data, t_config *config)
{
	int i;

	i = 0;
	while (param[i])
	{
		if (param[i][0] == '\n')
			i++;
		else if (valid_elements_pair(param[i][0], param[i][1] == 1) && config->count_param < 8)
			parse_param_line(param[i], data, config);
		else if (param[i][0] == '1' && config->count_param == 8)
			//map!
		else if (param[i][0] == ' ' && config->count_param == 8)
			//look what's next
		else
			return (error_handler(-3));
	}
}

/*
int extract_map_from_file(char *path_file, t_data *data)
{
	char	*tmp;
	char	**map;
	int		**map_tab;
	//int		r;

	//r = 0;
	map_tab = NULL;
	tmp = file_to_str(path_file);
	if (!tmp)
		return (error_handler(-1));
	r = pre_parsing(tmp);
	if (r < 0)
	{
		free(tmp);
		return (-1);
	}
	map = ft_lite_split(tmp, '\n');
	map_tab = malloc_2d_array(map_tab, map_max_width(map), map_max_height(map));
	str_to_array(map, map_tab, map_max_width(map), map_max_height(map));
	free(tmp);
	free_2d_string(map);
	free_2d_array(map_tab, map_max_height(map));
	return (1);
}*/

int extract_config_elements(t_data *data, char *path_file)
{
	char	*tmp;
	char	**param;

	tmp = file_to_str(path_file);
	if (!tmp)
		return (error_handler(-1));
	param = ft_lite_split(tmp, '\n');
	parsing_parameters(param, data, data->config);

}

int main(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	init_config(data);
	extract_map_from_file("./map_test.cub", data);
	free(data->config);
	free(data);
	return (1);
}
