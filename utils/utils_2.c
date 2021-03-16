/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:55:56 by calle             #+#    #+#             */
/*   Updated: 2021/03/16 12:45:05 by user42           ###   ########.fr       */
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

char	**calloc_2d_str(int size, int lines)
{
	int	i;
	char **str;

	i = 0;
	str = (char **)ft_calloc(lines + 1, sizeof(char *));
	if (!str)
		return (NULL);
	while (i < lines)
	{
		str[i] = (char *)ft_calloc(size + 1, sizeof(char));
		if (!str[i])
			return (NULL);
		i++;
	}
	return (str);
}

void	copy_2d_str(char **srcs, char **dest, int start, t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < data->world_ht)
	{
		i = 0;
		while (i < data->world_wd)
		{
			dest[j][i] = srcs[start + j][i];
			i++;
		}
		j++;
	}
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
