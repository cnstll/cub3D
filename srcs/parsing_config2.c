/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:34:16 by calle             #+#    #+#             */
/*   Updated: 2021/03/15 17:18:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int		check_path(char *p, int start)
{
	int j;

	j = start;
	while (p[j])
	{
		if (ft_isalpha(p[j]) == 1 || p[j] == '_' || p[j] == '/' || p[j] == '.')
		{
			if (p[j] == '/'
				&& (ft_isalpha(p[j + 1]) == 0 || p[j + 1] == '.'))
				return (-1);
			j++;
		}
		else
			return (-1);
	}
	return (1);
}

int		copy_path(char *p, t_config *config, int start)
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

int		valid_elements_pair(char e1, char e2)
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

int		check_parameters(t_config *config, int ret)
{
	if (!*config->tx_ea || !check_texture_file(config->tx_ea))
		ret = -6;
	else if (!*config->tx_so || !check_texture_file(config->tx_so))
		ret = -6;
	else if (!*config->tx_we || !check_texture_file(config->tx_we))
		ret = -6;
	else if (!*config->tx_no || !check_texture_file(config->tx_no))
		ret = -6;
	else if (!*config->tx_sprite || !check_texture_file(config->tx_sprite))
		ret = -6;
	else if (config->res_x < 1 || config->res_y < 1)
		ret = -6;
	else if (config->c_saved < 1 || config->f_saved < 1)
		ret = -6;
	return (ret);
}

int		check_if_map(char *line, int num_line, t_config *config)
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
