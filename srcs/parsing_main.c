/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:39:58 by calle             #+#    #+#             */
/*   Updated: 2021/03/16 17:23:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static int	map_pre_parsing(char **map, int start)
{
	int j;
	int num_of_init_pos;

	num_of_init_pos = 0;
	if (!map)
		return (-1);
	while (map[start])
	{
		j = 0;
		while (map[start][j])
		{
			if (c_in_s(map[start][j], " 012NSEW") == 0)
				return (-2);
			if (c_in_s(map[start][j], "NSEW") == 1)
				num_of_init_pos++;
			j++;
		}
		start++;
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

	i = 0;
	while (i < data->world_ht)
	{
		j = 0;
		while (j < data->world_wd)
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

int			check_empty_lines(char **map, t_data *data)
{
	int j;
	int i;
	int	l1;
	int	l2;
	int	l3;

	i = 0;
	l1 = 0;
	l2 = 0;
	l3 = 0;
	while (i < data->world_ht - 2)
	{
		j = 0;
		while (map[i][j] && j < data->world_wd)
		{
			l1 = 1;
			j++;
		}
		i++;
		if (l1 == 1 && l2 == 0 && l3 == 1)
			return (-7); 
	}
	return (1); 
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
	char **tmp;

	r = 0;
	r = map_pre_parsing(map, start);
	if (r < 0)
		return (r);
	data->world_wd = map_max_width(map, start);
	data->world_ht = map_max_height(map, start);
	tmp = calloc_2d_str(data->world_wd, data->world_ht);
	copy_2d_str(map, tmp, start, data);
	//r = check_empty_lines(tmp, data);
	//if (r < 0)
	//	return (r);
	r = check_map_golden_rule(tmp, 0);
	if (r < 0)
		return (r);
	data->world = malloc_2d_array(data->world, data->world_wd, data->world_ht);
	str_to_array(tmp, data->world, data, 0);
	free_2d_string(tmp);
	return (r);
}
