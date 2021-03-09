#ifndef _BMP_H
#define _BMP_H
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#pragma pack(push, 1)

typedef int int32;

typedef short int16;

typedef struct	s_img_header
{
	int32 size_img_header;
	int32 wd;
	int32 ht;
	int16 planes;
	int16 bpp;
	int32 compression;
	int32 size_img;
	int32 hres;
	int32 vres;
	int32 c_table;
	int32 c_img_table;
}				t_img_header;

typedef struct	s_head
{
	char			signature[2];
	int32			size;
	int32			reserved;
	int32			img_offset;
	t_img_header	img_head;
}				t_head;
#pragma pack(pop)

typedef struct	s_pixel
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_pixel;

typedef struct	s_bimg 
{
	int		w;
	int		h;
	t_pixel	*dat;
}				t_bimg;

int		copy_buffer_to_bimg(t_data *data, int **buf);
t_bimg	*new_bmp_img(int w, int h);
t_bimg	*cpy_bmp_img(t_bimg *bimg);
void	del_bmp_img(t_bimg *bimg);
int		set_pixel(t_bimg *bimg, int i, int j, t_pixel p);
t_pixel	get_pixel(t_bimg *bimg, int i, int j);
#endif
 
