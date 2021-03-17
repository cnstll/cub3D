/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <calle@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 10:21:59 by user42            #+#    #+#             */
/*   Updated: 2021/03/17 16:41:01 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void		init_head(t_head *head, t_bimg *bimg)
{
	head->signature[0] = 'B';
	head->signature[1] = 'M';
	head->img_offset = sizeof(t_head);
	head->img_head.size_img_header = sizeof(t_img_header);
	head->img_head.wd = bimg->w;
	head->img_head.ht = bimg->h;
	head->img_head.planes = 1;
	head->img_head.bpp = 24;
}

static int		hexa_to_rgb(int color, char rgb)
{
	if (rgb == 'R')
		return ((color & 0xff0000) >> 16);
	if (rgb == 'G')
		return ((color & 0x00ff00) >> 8);
	if (rgb == 'B')
		return (color & 0x0000ff);
	return (-1);
}

static void		write_pixels(int pitch, t_bimg *bimg, int fd)
{
	int				i;
	int				j;
	unsigned char	bgr_pix[3];
	t_pixel			p;

	i = 0;
	while (i < bimg->h)
	{
		j = 0;
		while (j < bimg->w)
		{
			p = get_pixel(bimg, bimg->h - i - 1, j);
			bgr_pix[0] = p.b;
			bgr_pix[1] = p.g;
			bgr_pix[2] = p.r;
			write(fd, &bgr_pix, 3);
			j++;
		}
		bgr_pix[0] = 0;
		bgr_pix[1] = 0;
		bgr_pix[2] = 0;
		write(fd, &bgr_pix, pitch);
		i++;
	}
}

static int		save_img(t_bimg *bimg, const char *file)
{
	t_head		head;
	int			pitch;
	int			data_size;
	static char	corrpitch[4] = {0, 3, 2, 1};
	int			fd;

	fd = open(file, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG);
	if (fd < 0)
		return (-1);
	ft_memset(&head, 0, sizeof(t_head));
	init_head(&head, bimg);
	pitch = corrpitch[(3 * head.img_head.wd) % 4];
	data_size = 3 * head.img_head.ht * head.img_head.wd
				+ head.img_head.ht * pitch;
	head.img_head.size_img = data_size;
	head.size = head.img_offset + head.img_head.size_img;
	write(fd, &head, sizeof(t_head));
	write_pixels(pitch, bimg, fd);
	close(fd);
	return (0);
}

int				copy_buffer_to_bimg(t_data *data, int **buf)
{
	int		i;
	int		j;
	t_bimg	*bimg;
	t_pixel	p;

	i = 0;
	bimg = new_bmp_img(data->screen_wd, data->screen_ht);
	while (i < data->screen_ht)
	{
		j = 0;
		while (j < data->screen_wd)
		{
			p.r = hexa_to_rgb(buf[i][j], 'R');
			p.g = hexa_to_rgb(buf[i][j], 'G');
			p.b = hexa_to_rgb(buf[i][j], 'B');
			set_pixel(bimg, i, j, p);
			j++;
		}
		i++;
	}
	save_img(bimg, "save.bmp");
	del_bmp_img(bimg);
	return (0);
}
