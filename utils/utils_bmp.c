#include "./bmp.h"

Image* NouvelleImage(int w,int h)
{
	Image* I = malloc(sizeof(Image));
	I->w = w;
	I->h = h;
	I->dat = calloc(1,w*h*sizeof(Pixel*));
	return I;
}

Image* CopieImage(Image* I)
{
	Image* res;
	if (!I)
		return NULL;
	res = NouvelleImage(I->w,I->h);
	memcpy(res->dat,I->dat,I->w*I->h*sizeof(Pixel));
	return res;
}

void DelImage(Image* I)
{
	if (I)
	{
		free(I->dat);
		free(I);
	}
}

int	SetPixel(Image* I,int i,int j,Pixel p)
{
	I->dat[I->w * j + i] = p;
	return (1);
}

Pixel GetPixel(Image* I,int i,int j)
{
	return I->dat[I->w * j + i];
}
