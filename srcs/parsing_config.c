#include "../includes/cube.h"

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
