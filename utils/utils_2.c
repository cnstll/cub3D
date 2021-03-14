/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:55:56 by calle             #+#    #+#             */
/*   Updated: 2021/03/14 16:56:19 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	free_2d_string(char **s)
{
	int i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

void	free_2d_array(int **array, int num_lines)
{
	int	i;

	i = 0;
	while (i < num_lines)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int		**malloc_2d_array(int **array, int size, int lines)
{
	int	i;

	i = 0;
	array = (int **)malloc(lines * sizeof(int *));
	if (!array)
		return (NULL);
	while (i < lines)
	{
		array[i] = (int *)malloc(size * sizeof(int));
		if (!array[i])
			return (NULL);
		i++;
	}
	return (array);
}
