/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:16:22 by calle             #+#    #+#             */
/*   Updated: 2021/03/17 18:21:43 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BMP_H
# define _BMP_H
# include <stdint.h>
# pragma pack(push, 1)

typedef struct	s_img_header
{
	int32_t size_img_header;
	int32_t wd;
	int32_t ht;
	int16_t planes;
	int16_t bpp;
	int32_t compression;
	int32_t size_img;
	int32_t hres;
	int32_t vres;
	int32_t c_table;
	int32_t c_img_table;
}				t_img_header;

typedef struct	s_head
{
	char			signature[2];
	int32_t			size;
	int32_t			reserved;
	int32_t			img_offset;
	t_img_header	img_head;
}				t_head;
# pragma pack(pop)

typedef struct	s_pixel
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_pixel;

typedef struct	s_bimg
{
	int			w;
	int			h;
	t_pixel		*dat;
}				t_bimg;

int				copy_buffer_to_bimg(t_data *data, int **buf);
t_bimg			*new_bmp_img(int w, int h);
t_bimg			*cpy_bmp_img(t_bimg *bimg);
void			del_bmp_img(t_bimg *bimg);
int				set_pixel(t_bimg *bimg, int i, int j, t_pixel p);
t_pixel			get_pixel(t_bimg *bimg, int i, int j);
unsigned long	rgb_to_hex(int r, int g, int b);
#endif
