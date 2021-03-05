#include "./bmp.h"

int main()
{
	int i,j;
	Image* I = NouvelleImage(256,256);
	for(i=0;i<256;i++)
	{
		for(j=0;j<256;j++)
		{
			Pixel p;
			p.r = i;
			p.g = j;
			p.b = 0;
			SetPixel(I,i,j,p);
		}
	}
	//Image* I = Charger("test.bmp");
	Sauver(I,"test.bmp");
	DelImage(I);
	return 0;
}
