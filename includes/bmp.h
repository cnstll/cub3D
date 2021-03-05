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

struct BMPImHead
{
	int32 size_imhead;
	int32 width;
	int32 height;
	int16 nbplans; // toujours 1
	int16 bpp;
	int32 compression;
	int32 sizeim;
	int32 hres;
	int32 vres;
	int32 cpalette;
	int32 cIpalette;
};

struct BMPHead
{
	char signature[2];
	int32 taille;
	int32 rsv;
	int32 offsetim;
	struct BMPImHead imhead;
};
#pragma pack(pop)

typedef struct Pixel
{
	unsigned char r,g,b;
} Pixel;

typedef struct Image
{
	int w,h;
	Pixel* dat;
} Image;

Image* Charger(const char* fichier);
int Sauver(Image*,const char* fichier);
Image* NouvelleImage(int w,int h);
Image* CopieImage(Image*);
int SetPixel(Image*,int i,int j,Pixel p);
Pixel GetPixel(Image*,int i,int j);
void DelImage(Image*);

#endif
 
