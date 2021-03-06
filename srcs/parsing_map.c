/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:42:59 by calle             #+#    #+#             */
/*   Updated: 2021/03/21 19:07:46 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static int	apply_golden_rule(char **map, int i, int j)
{
	if (c_in_s(map[i - 1][j - 1], " 1") == 0)
		return (-7);
	else if (c_in_s(map[i - 1][j], " 1") == 0)
		return (-7);
	else if (c_in_s(map[i - 1][j + 1], " 1") == 0)
		return (-7);
	else if (c_in_s(map[i][j - 1], " 1") == 0)
		return (-7);
	else if (c_in_s(map[i][j + 1], " 1") == 0)
		return (-7);
	else if (c_in_s(map[i + 1][j - 1], " 1") == 0)
		return (-7);
	else if (c_in_s(map[i + 1][j], " 1") == 0)
		return (-7);
	else if (c_in_s(map[i + 1][j + 1], " 1") == 0)
		return (-7);
	return (1);
}

static int	check_n_w(char **map, int i, int j, int start)
{
	if (i - start == 0 && map[i][j] == ' ')
	{
		if (j != 0 && map[i + 1][j - 1] && !c_in_s(map[i + 1][j - 1], " 1"))
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

static int	check_e(char **map, int i, int j)
{
	if (!map[i][j + 1] && map[i][j] == ' ')
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

static int	check_borders(char **map, int i, int j, int start)
{
	if (!c_in_s(map[i][j], " 1") && map[i][j])
		return (-7);
	if (map[i][j] == '1')
		return (1);
	if ((j == 0 || i - start == 0))
		return (check_n_w(map, i, j, start));
	else if (!map[i - 1][j] && map[i][j] == ' ')
	{
		if (map[i + 1][j - 1] && !c_in_s(map[i + 1][j - 1], " 1"))
			return (-7);
		if (map[i + 1][j] && !c_in_s(map[i + 1][j], " 1"))
			return (-7);
		if (map[i + 1][j + 1] && !c_in_s(map[i + 1][j + 1], " 1"))
			return (-7);
	}
	else if (!map[i][j + 1] && map[i][j] == ' ')
		return (check_e(map, i, j));
	else if (!map[i + 1][j] && map[i][j] == ' ')
		return (check_e(map, i, j));
	else
		return (apply_golden_rule(map, i, j));
	return (1);
}

int			check_map_golden_rule(char **map, int start)
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
			if (is_border(map, i, j, start) < 0 && map[i][j] == ' ')
				r = apply_golden_rule(map, i, j);
			else if (is_border(map, i, j, start) > 0)
				r = check_borders(map, i, j, start);
			j++;
		}
		i++;
	}
	return (r);
}
