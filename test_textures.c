#include "./includes/cube.h"

typedef struct  s_data {
	void        *img;
	void        *tx;
	char        *addr;
	char        *tx_addr;
	int         bpp;
	int         line_len;
	int         endian;
	int         tx_bpp;
	int         tx_line_len;
	int         tx_endian;
	void		*mlx;
	void		*win;
	int			x;
	int			y;
	int			x_screen;
	int			y_screen;
	int			width;
	int			height;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, char *color)
{
	unsigned char    *src;
	unsigned char    r;
	unsigned char    g;
	unsigned char    b;

	printf("color - %s\n", color);
	src = (unsigned char *)color;
	r = src[0];
	printf("r - %u\n", r);
	g = src[1];
	printf("g - %u\n", g);
	b = src[2];
	printf("b - %u\n", b);
	printf("pre tx_addr\n");
	data->addr[y * data->line_len + x * data->bpp / 8] = r;
	data->addr[y * data->line_len + x * data->bpp / 8 + 1] = g;
	data->addr[y * data->line_len + x * data->bpp / 8 + 2] = b;
	printf("post tx_addr\n");
}

int load_textured_img(t_data *data)
{
	data->tx = mlx_xpm_file_to_image(data->mlx , "./textures/redbrick.xpm", &data->width, &data->height);
	data->tx_addr = mlx_get_data_addr(data->tx, &data->tx_bpp, &data->tx_line_len,
				&data->tx_endian);
	printf("textures width - %d\n", data->width);
	printf("textures height - %d\n", data->height);
//	mlx_put_image_to_window(data->mlx, data->win, data->tx, 32, 32);
	return (1);
}

/*int put_textured_img(t_data *data)
{
	data->img = mlx_xpm_file_to_image(data->mlx , "./textures/wood.xpm", &data->width, &data->height);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len,
				&data->endian);
	printf("textures width - %d\n", data->width);
	printf("textures height - %d\n", data->height);
	mlx_put_image_to_window(data->mlx, data->win, data->img, data->x, data->y);
	return (1);
}*/
int put_texel(t_data *data)
{
	int x;
	int y;
	
	y = 0;
	while (y < 64)
	{
		x = 0;
		while (x < 64)
		{
			my_mlx_pixel_put(data, 320 + x, 240 + y, &data->tx_addr[x + y * 64]);	
			printf("pixel printed - %d\n", x + y * 64); 
			x++;
		}
		y++;
	}
	return (1);
}

int main()
{
	t_data img;

	img.x = 320;
	img.y = 240;
	img.x_screen = 640;
	img.y_screen = 480;
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, img.x_screen, img.y_screen, "cub3D");
	img.img = mlx_new_image(img.mlx, img.x_screen, img.y_screen);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len,
				&img.endian);
	//put_textured_img(&img);
	load_textured_img(&img);
	put_texel(&img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_loop(img.mlx);	
}
