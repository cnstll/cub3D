#include "./bmp.h"
int	init_head(t_head head)
{
	int	data_size;

	data_size = 0;
	head.signature[0] = 'B';
	head.signature[1] = 'M';
	head.img_offset = sizeof(t_head);
	head.img_head.size_img_head = sizeof(t_head);
	head.img_head.wd = I->w;
	head.img_head.ht = I->h;
	head.img_head.planes = 1;
	head.img_head.bpp = 24;
	data_size = 3 * head.img_head.ht * head.img_head.wd 
				+ head.img_head.ht * pitch;
	head.img_head.size_img = data_size;
	head.size = head.img_offset + head.img_head.size_img;
}

void	write_pixels(int pitch)
{
	int	i;
	int	j;
	unsigned char bgrpix[3];

	i = 0;
	while (i < I->h)
	{
		j = 0;
		while (j < I->w)
		{
			p = GetPixel(I,i,I->h-j-1);
			bgrpix[0] = p.b;
			bgrpix[1] = p.g;
			bgrpix[2] = p.r;
			write(fd, &bgrpix ,3);
			j++;
		}
		bgrpix[0] = bgrpix[1] = bgrpix[2] = 0;
		write(fd, &bgrpix, pitch);
		i++;
	}
}

int save_img(b_img* bimg, const char *file)
{
	t_head head;
	Pixel p;
	int pitch;
	char corrpitch[4] = {0,3,2,1};
	int fd;
	fd = open(file, O_CREAT|O_RDWR, S_IRWXU|S_IRWXG);
	if (fd < 0)
		return -1;
	memset(&head, 0, sizeof(struct BMPHead));
	init_head(head);
	pitch = corrpitch[(3 * head.img_head.wd) % 4];
	write(fd, &head, sizeof(struct t_head));
	close(fd);
	return 0;
}

int		copy_buffer(t_data *data, int **buf) 
{
	int	i;
	int	j;

	i = 0;
	Image* I = NouvelleImage(data->screen_wd,data->screen_ht);
	while (i < data->screen_ht)
	{
		j = 0;
		while (j < data->screen_wd)
		{
			Pixel p;
			p.r = i;
			p.g = j;
			p.b = 0;
			SetPixel(I,i,j,p);
			j++;
		}
		i++;
	}
	Sauver(I,"test.bmp");
	DelImage(I);
	return 0;
}
