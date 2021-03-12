/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sorter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:57:51 by calle             #+#    #+#             */
/*   Updated: 2021/02/23 23:03:23 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	swap_double(double *a, double *b)
{
	double tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	swap_sp(t_sp *a, t_sp *b)
{
	t_sp tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void		bubble_sort(t_sprite *sprite, double *array, int size)
{
	int i;
	int	done;

	done = 1;
	while (done > 0)
	{
		i = 0;
		while (i < size - 1)
		{
			if (array[i] < array[i + 1])
			{
				swap_double(&array[i], &array[i + 1]);
				swap_sp(&sprite->sp[i], &sprite->sp[i + 1]);
				done++;
			}
			else if (array[i] > array[i + 1])
				done--;
			i++;
		}
		if (i == 0)
			done = 0;
	}
}
