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
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int main(void)
{
	void *mlx;
	void *mlx_win;
	t_data img;
	int i;
	int j;


	i = 0;
	j = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 680, "cub3D");
	img.img = mlx_new_image(mlx, 800, 680);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    while (j < 680)
	{
		i += 5;
		j += 5;
		my_mlx_pixel_put(&img, i, j, 0x00FF0000);
    }
    i = 15;
	j = 0;
	while (j < 680)
	{
		i += 5;
		j += 5;
		my_mlx_pixel_put(&img, i, j, 0x00F0FF00);
    }
    i = 30;
	j = 0;
	while (j < 680)
	{
		i += 5;
		j += 5;
		my_mlx_pixel_put(&img, i, j, 0x0015FF00);
    }
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}
