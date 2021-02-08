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
	int			keycode;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	print_vertical_line(t_data *data, int x, int y_max, int color)
{
	int		y;

	y = 0;
	while (y < y_max)
	{
		y += 1;
		my_mlx_pixel_put(data, x, y, color);
    }
}

int             key_hook(int keycode, t_data data)
{
    printf("keycode is %d\n", keycode);
	data.keycode = keycode;
	if (keycode == 13)
	{
		data.y -= 5;
		my_mlx_pixel_put(&data, data.x, data.y, 0x00FF0000);	
		printf("You moved forward\n");
	}
    if (keycode == 1)
	{
		printf("You moved backward\n");
	}
    if (keycode == 0)
	{
		printf("You moved left\n");
	}
    if (keycode == 2)
	{
		printf("You moved right\n");
	}
    if (keycode == 124)
	{
		printf("You moved your sight to the right\n");
	}
    if (keycode == 123)
	{
		printf("You moved your sight to the left\n");
	}
	if (keycode == 53)
	{
		printf("You ESC the game\n");
	}
}

int		mouse_hook(int mouse, int x, int y, t_data data)
{
    printf("mouse is %d\n", mouse);
    printf("mouse position %d:%d\n", x, y);
	if (mouse  == 1)
	{
		printf("Left Click\n");
	}
	if (mouse  == 2)
	{
		printf("Right Click\n");
	}
}

int		close (int keycode, t_data *data)
{
	if (keycode == 53)
	{
		printf("You ESC the game\n");
		mlx_destroy_window(data->mlx, data->win);
//		mlx_loop_end(data->mlx);
	}
}

/*void		resize(int *sizex, int *sizey, t_data *data)
{
	mlx_get_screen_size(data->mlx, sizex, sizey);
	printf("Window is of size %d:%d\n", *sizex, *sizey);
}*/

int		render_next_frame(t_data *data)
{
	
	if (data->keycode == 13)
	{
		my_mlx_pixel_put(data, data->x, data->y - 10, 0x00FF0000);	
		printf("You moved forward\n");

	}
    if (data->keycode == 1)
	{
		my_mlx_pixel_put(data, data->x, data->y + 10, 0x00FF0000);	
		printf("You moved backward\n");
	}
    if (data->keycode == 0)
	{
		my_mlx_pixel_put(data, data->x - 10, data->y, 0x00FF0000);	
		printf("You moved left\n");
	}
    if (data->keycode == 2)
	{
		my_mlx_pixel_put(data, data->x + 10, data->y, 0x00FF0000);	
		printf("You moved right\n");
	}

}

int main(void)
{
	t_data img;

	img.x = 320;
	img.y = 240;
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, 640, 480, "cub3D");
	img.img = mlx_new_image(img.mlx, 640, 480);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                &img.endian);
	
	
	my_mlx_pixel_put(&img, img.x, img.y, 0x00FF0000);	
	mlx_key_hook(img.win, key_hook, &img);
	//mlx_mouse_hook(img.win, mouse_hook, &img);
	//mlx_hook(img.win, 2, 1L<<0, close, &img);
	//my_mlx_pixel_put(&img, img.x, img.y, 0x00FF0000);	
	//my_mlx_pixel_put(&img, 320, 240, 0x00FF0000);	
	//mlx_loop_hook(img.mlx, render_next_frame, &img);
	//mlx_loop_hook(img.mlx, render_next_frame, &img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_loop(img.mlx);
}
