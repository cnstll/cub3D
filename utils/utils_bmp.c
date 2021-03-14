/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 17:02:54 by calle             #+#    #+#             */
/*   Updated: 2021/03/14 17:04:31 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

t_bimg	*new_bmp_img(int w, int h)
{
	t_bimg *bimg;

	bimg = malloc(sizeof(t_bimg));
	bimg->w = w;
	bimg->h = h;
	bimg->dat = ft_calloc(1, w * h * sizeof(t_pixel *));
	return (bimg);
}

t_bimg	*cpy_bmp_img(t_bimg *bimg)
{
	t_bimg *cp;

	if (!bimg)
		return (NULL);
	cp = new_bmp_img(bimg->w, bimg->h);
	ft_memcpy(cp->dat, bimg->dat, bimg->w * bimg->h * sizeof(t_pixel));
	return (cp);
}

void	del_bmp_img(t_bimg *bimg)
{
	if (bimg)
	{
		free(bimg->dat);
		free(bimg);
	}
}

int		set_pixel(t_bimg *bimg, int i, int j, t_pixel p)
{
	if (j < 0)
		j = 0;
	if (i < 0)
		i = 0;
	bimg->dat[bimg->w * j + i] = p;
	return (1);
}

t_pixel	get_pixel(t_bimg *bimg, int i, int j)
{
	if (j < 0)
		j = 0;
	if (i < 0)
		i = 0;
	return (bimg->dat[bimg->w * j + i]);
}
