/* Parsing of the map to check if the map is valid
   and find the initial position of the player */

/* What is a valid map ?
   - A '0', '2', 'N', 'S', 'E', 'W',  cannot have a contiguous ' ' or !c
   - A '0', '2', 'N', 'S', 'E', 'W', cannot be in the first position of a row or the last one
   - A '0', '2', 'N', 'S', 'E', 'W', cannot be in the first row or the last row
   */
/*	
	char map[8][8] = {	{'1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', 'N', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1'}};
	*/

#include "cube.h"

typedef struct	s_img_param {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}				t_img_param;	

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
	void		*mlx;
	void		*win;
	int			x;
	int			y;
	int			x_screen;
	int			y_screen;
	int			width;
	int			height;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void init_img(t_data *data)
{

	//data->img = mlx_new_image(data->mlx, data->x_screen, data->y_screen);
	//	data->img = mlx_xpm_file_to_image(data->mlx , "./pacman.xpm", &data->width, &data->height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
				&data->endian);
}

int put_textured_img(t_data *data)
{
	data->img = mlx_xpm_file_to_image(data->mlx , "./pacman.xpm", &data->width, &data->height);
	mlx_put_image_to_window(data->mlx, data->win, data->img, data->x, data->y);
	return (1);
}

int             key_hook(int keycode, t_data *data)
{
	if (keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2)
	{
		mlx_destroy_image(data->mlx, data->img);
		printf("img destroyed !\n");
	}
	if (keycode == 13)
	{
		data->y -= 10;
		put_textured_img(data);
		printf("You moved forward\n");

	}
	if (keycode == 1)
	{
		data->y += 10;
		put_textured_img(data);
		printf("You moved backward\n");
	}
	if (keycode == 0)
	{
		data->x -= 10;
		put_textured_img(data);
		printf("You moved left\n");
	}
	if (keycode == 2)
	{
		data->x += 10;
		put_textured_img(data);
		printf("You moved right\n");
	}
}

int main(void)
{
	t_data img;

	img.x = 320;
	img.y = 240;
	img.x_screen = 640;
	img.y_screen = 480;
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, img.x_screen, img.y_screen, "cub3D");
	init_img(&img);
	put_textured_img(&img);
	mlx_key_hook(img.win, key_hook, &img);
	mlx_loop(img.mlx);
}


int print_background(t_data *data)
{
	//my_mlx_pixel_put(data, data->x, data->y, 0x00FF0000);	
	return (1);
}

int print_wall()
{
	/*	while (img.y < 480 - height) 
		{	
		img.x = 0;
		while (img.x < 640 - width)
		{	
		mlx_put_image_to_window(img.mlx, img.win, img.img, img.x, img.y);
		img.x = img.x + width;
		}
		img.y = img.y + height;
		}
		*/
	return (1);
}

