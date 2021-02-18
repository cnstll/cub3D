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
	int			x_screen;
	int			y_screen;
	int			width;
	int			height;
}               t_data;

/*void            my_mlx_pixel_put(t_data *data, int x, int y, char *color)
  {
  unsigned char    *src;
  unsigned char    r;
  unsigned char    g;
  unsigned char    b;

///printf("color - %x\n", color);
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
}*/

void	pixel_put(t_data *data, int x, int y, int color)
{
	char    *pixel;

	pixel = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(int *)pixel = color;
}

int load_texture(t_data *data)
{
	data->tx = mlx_xpm_file_to_image(data->mlx, "./textures/wood.xpm", &data->width, &data->height);
	data->tx_addr = mlx_get_data_addr(data->tx, &data->tx_bpp, &data->tx_line_len,
			&data->tx_endian);
	//	mlx_put_image_to_window(data->mlx, data->win, data->tx, 32, 32);
	return (1);
}

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
			data->addr[y * data->line_len + x * data->bpp / 8] =
				data->tx_addr[ y * data->tx_line_len + x * data->tx_bpp / 8];
			data->addr[y * data->line_len + x * data->bpp / 8 + 1] =
				data->tx_addr[ y * data->tx_line_len + x * data->tx_bpp / 8 + 1];
			data->addr[y * data->line_len + x * data->bpp / 8 + 2] = 
				data->tx_addr[ y * data->tx_line_len + x * data->tx_bpp / 8 + 2];
			x++;
		}
		y++;
	}
	return (1);
}

int main()
{
	t_data *data;

	data = malloc(sizeof(t_data));
	data->x_screen = 640;
	data->y_screen = 480;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->x_screen, data->y_screen, "cub3D");
	data->img = mlx_new_image(data->mlx, data->x_screen, data->y_screen);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len,
			&data->endian);
	//put_textured_data->&data->;
	load_texture(data);
	put_texel(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop(data->mlx);	
	free(data);
}
