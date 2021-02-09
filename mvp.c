/* Parsing of the map to check if the map is valid
and find the initial position of the player */

/* What is a valid map ?
- A '0', '2', 'N', 'S', 'E', 'W',  cannot have a contiguous ' ' or !c
- A '0', '2', 'N', 'S', 'E', 'W', cannot be in the first position of a row or the last one
- A '0', '2', 'N', 'S', 'E', 'W', cannot be in the first row or the last row
*/

#include "cube.h"

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
	int			keycode;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void init_img(t_data *data)
{

	data->img = mlx_new_image(data->mlx, data->x_screen, data->y_screen);
   	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
                                &data->endian);
}

int             key_hook(int keycode, t_data *data)
{
	data->keycode = keycode;
	if (data->keycode == 13 || data->keycode == 1 || data->keycode == 0 || data->keycode == 2)
	{
		mlx_destroy_image(data->mlx, data->img);
		init_img(data);
	}
	if (data->keycode == 13)
	{
		data->y -= 10;
		my_mlx_pixel_put(data, data->x, data->y, 0x00FF0000);	
		printf("You moved forward\n");

	}
    if (data->keycode == 1)
	{
		data->y += 10;
		my_mlx_pixel_put(data, data->x, data->y, 0x00FF0000);	
		printf("You moved backward\n");
	}
    if (data->keycode == 0)
	{
		data->x -= 10;
		my_mlx_pixel_put(data, data->x, data->y, 0x00FF0000);	
		printf("You moved left\n");
	}
    if (data->keycode == 2)
	{
		data->x += 10;
		my_mlx_pixel_put(data, data->x, data->y, 0x00FF0000);	
		printf("You moved right\n");
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int main(void)
{
	t_data img;
	int width;	
	int height;
	char map[8][8] = {	{'1', '1', '1', '1', '1', '1', '1', '1'},
						{'1', '0', '0', '0', '0', '0', '0', '1'},
						{'1', '0', '1', 'N', '0', '0', '0', '1'},
						{'1', '0', '1', '0', '0', '0', '0', '1'},
						{'1', '0', '0', '0', '0', '1', '0', '1'},
						{'1', '0', '0', '0', '1', '1', '0', '1'},
						{'1', '0', '0', '0', '0', '0', '0', '1'},
						{'1', '1', '1', '1', '1', '1', '1', '1'}};
	img.x = 0;
	img.y = 0;
	img.x_screen = 640;
	img.y_screen = 480;
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, img.x_screen, img.y_screen, "cub3D");
	init_img(&img);
	//	mlx_key_hook(img.win, key_hook, &img);
	img.img = mlx_xpm_file_to_image (img.mlx , "./pacman.xpm", &width, &height);
	while (img.y < 480) 
	{	
		img.x = 0;
		while (img.x < 640)
		{	
			mlx_put_image_to_window(img.mlx, img.win, img.img, img.x, img.y);
			img.x = img.x + width;
		}
		img.y = img.y + height;
	}
	mlx_loop(img.mlx);
}
