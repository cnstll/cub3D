/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:56:25 by calle             #+#    #+#             */
/*   Updated: 2021/03/17 16:57:03 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	is_border(char **map, int i, int j, int start)
{
	if (j == 0 || i - start == 0)
		return (1);
	else if (!map[i - 1][j - 1] || !map[i - 1][j] || !map[i - 1][j + 1])
		return (1);
	else if (!map[i + 1][j - 1] || !map[i + 1][j] || !map[i + 1][j + 1])
		return (1);
	else if (!map[i][j - 1] || !map[i - 1][j - 1] || !map[i + 1][j - 1])
		return (1);
	else if (!map[i][j + 1] || !map[i - 1][j + 1] || !map[i + 1][j + 1])
		return (1);
	return (-1);
}
