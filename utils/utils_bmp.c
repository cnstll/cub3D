#include "./bmp.h"

bimg* new_bmp_img(int w, int h)
{
	bimg* bimg;

	bimg = malloc(sizeof(bimg));
	bimg->w = w;
	bimg->h = h;
	bimg->dat = calloc(1, w * h * sizeof(t_pixel*));
	return (bimg);;
}

bimg* cpy_bmp_img(bimg* bimg)
{
	bimg* cp;
	
	if (!bimg)
		return NULL;
	cp = new_bmp_img(bimg->w, bimg->h);
	memcpy(cp->dat, bimg->dat, bimg->w * bimg->h * sizeof(t_pixel));
	return (cp);
}

void del_bmp_img(bimg* bimg)
{
	if (bimg)
	{
		free(bimg->dat);
		free(bimg);
	}
}

int	set_pixel(bimg* bimg, int i, int j, t_pixel p)
{
	bimg->dat[bimg->w * j + i] = p;
	return (1);
}

t_pixel get_pixel(bimg* bimg, int i, int j)
{
	return bimg->dat[bimg->w * j + i];
}
