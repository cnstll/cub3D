#include "./bmp.h"

int	init_head(t_head head)
{
	head.signature[0] = 'B';
	head.signature[1] = 'M';
	head.offsetim = sizeof(t_head);
	head.imhead.size_imhead = sizeof(t_head);
	head.imhead.width = I->w;
	head.imhead.height = I->h;
	head.imhead.nbplans = 1;
	head.imhead.bpp = 24;
	tailledata = 3*head.imhead.height*head.imhead.width + head.imhead.height*pitch;
	head.imhead.sizeim = tailledata;
	head.taille = head.offsetim + head.imhead.sizeim;
}

void	write_pixels(int pitch)
{
	int	i;
	int	j;
	unsigned char bgrpix[3];

	for(j=0;j<I->h;j++)
	{
		for(i=0;i<I->w;i++)
		{
			p = GetPixel(I,i,I->h-j-1);
			bgrpix[0] = p.b;
			bgrpix[1] = p.g;
			bgrpix[2] = p.r;
			write(fd, &bgrpix ,3);
		}
		bgrpix[0] = bgrpix[1] = bgrpix[2] = 0;
		write(fd, &bgrpix, pitch);
	}
}

int save_img(Image* I, const char *fichier)
{
	t_head head;
	Pixel p;
	int tailledata;
	int pitch;
	char corrpitch[4] = {0,3,2,1};
	int fd;
	fd = open(fichier, O_CREAT|O_RDWR, S_IRWXU|S_IRWXG);
	if (fd < 0)
		return -1;
	memset(&head,0,sizeof(struct BMPHead));
	init_head(head);
	pitch = corrpitch[(3*head.imhead.width)%4];
	write(fd, &head, sizeof(struct BMPHead));
	close(fd);
	return 0;
}

