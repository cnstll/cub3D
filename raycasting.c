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
#define WORLD_WD 24
#define WORLD_HT 24
#define TEXTR_WD 64
#define TEXTR_HT 64

int		init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (-1);
	data->screen_wd = 640;
	data->screen_ht = 480;
	data->win = mlx_new_window(data->mlx, data->screen_wd, data->screen_ht, "cub3D");
	if (data->win == NULL)
		return (-1);
	return (1);
}

int		init_img(t_data *data)
{
//	if (data->img)
//		free(data->img);
	data->img = malloc(sizeof(t_img));
	data->img->time = 0; //time of current frame
	data->img->old_time = 0; //time of previous fram
	data->img->img = mlx_new_image(data->mlx, data->screen_wd, data->screen_ht);
	data->img->addr = (int *)mlx_get_data_addr(data->img->img, &data->img->bpp, &data->img->line_len, &data->img->endian);
	return (1);
}

int		init_ray(t_data *data)
{
//	if (data->ray)
//		free(data->img);
	data->ray = malloc(sizeof(t_ray));
	data->ray->pos_x = 18;
	data->ray->pos_y = 18;  //x and y start position
	data->ray->ms = 0.1;
	data->ray->rs = 0.1;
	data->ray->dir_x = -1;
	data->ray->dir_y = 0; //initial direction vector
	data->ray->plane_x = 0;
	data->ray->plane_y = 0.66; //the 2d raycaster version of camera plane
	return (1);
}

void init_array(int src_array[WORLD_WD][WORLD_HT], int dest_array[WORLD_WD][WORLD_HT])  
{
	int x;
	int y;

	x = 0;
	while (x < 24)
	{
		y = 0;
		while (y < 24)
		{
			dest_array[x][y] = src_array[x][y];
			y++;
		}
		x++;
	}
}

void print_array(int src_array[WORLD_WD][WORLD_HT])
{
	int x;
	int y;

	x = 0;
	while (x < 24)
	{
		y = 0;
		while (y < 24)
		{
			printf("%d", src_array[x][y]);
			if (y != 23)
				printf(" ");
			else
				printf("\n");
			y++;
		}
		x++;
	}
}

int malloc_2d_array(int **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		array[i] = malloc(size * sizeof(*array[i]));
		i++;
	}
	return (1);
}

/*
int put_stripes(t_data *data, int x, int start, int end, int color)
{
	int i;

	i = start;
	while (i <= end)
	{
		my_mlx_pixel_put(data->img, x, i, color);
		i++;
	}
	return (1);
}
*/
int draw_buffer(int **buffer, t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->screen_ht)
	{
		x = 0;
		while(x < data->screen_wd)
		{
			data->img->addr[x + y * data->screen_wd] = buffer[y][x];
			x++;
		}
		y++;
	}
	printf("max x - %d - max y - %d\n", x, y);
	return (1);
}

int clear_buffer(int **buffer, t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->screen_ht)
	{
		x = 0;
		while(x < data->screen_wd)
		{
			buffer[y][x] = 0; //clear the buffer
			x++;
		}
		y++;
	}
	return (1);
}

int print_buffer(int **buffer, t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->screen_ht)
	{
		x = 0;
		while(x < data->screen_wd)
		{
			printf("%d ",buffer[y][x]); //clear the buffer
			x++;
		}
		printf("\n");
		y++;
	}
	return (1);
}

int cast_img(t_data *data)
{
	int stripes;
	int max_stripes;
	int map_x;
	int map_y;
	//length of ray from current position to next x or y-side
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	double wall_dist;
	//what direction to step in x or y-direction (either +1 or -1)
	int step_x;
	int step_y;
	int hit;
	int side; //was a NS or a EW wall hit?
	int line_height;
	//drawing wall height
	int draw_start;
	int draw_end;
	int **buffer;
	buffer = malloc(sizeof(*buffer) * data->screen_ht); // y-coordinate first because it works per scanline
	malloc_2d_array(buffer, data->screen_wd);
	stripes = 0;
	max_stripes = 640;
	//printf("Before raycasting loop\n");
	while (stripes < max_stripes)
	{
		data->ray->camera_x = 2 * stripes / (double)(max_stripes) - 1; //x-coordinate in camera space
		data->ray->ray_dir_x = data->ray->dir_x + data->ray->plane_x * data->ray->camera_x;
		data->ray->ray_dir_y = data->ray->dir_y + data->ray->plane_y * data->ray->camera_x;

		//which box of the map we're in
		map_x = (int)(data->ray->pos_x);
		map_y = (int)(data->ray->pos_y);

		//length of ray from one x or y-side to next x or y-side
		if (data->ray->ray_dir_y == 0)
			delta_dist_x = 0;
		else if (data->ray->ray_dir_x == 1)
			delta_dist_x = 1;
		else
			delta_dist_x = fabs(1 / data->ray->ray_dir_x);
		if (data->ray->ray_dir_x == 0)
			delta_dist_y = 0;
		else if (data->ray->ray_dir_y == 1)
			delta_dist_y = 1;
		else
			delta_dist_y = fabs(1 / data->ray->ray_dir_y);
		//was there a wall hit?
		hit = 0;
		//printf("Looking for a wall\n");
		if (data->ray->ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->ray->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->ray->pos_x) * delta_dist_x;
		}
		if (data->ray->ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->ray->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->ray->pos_y) * delta_dist_y;
		}

		//perform DDA
		//printf("Perform DDA\n");
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (data->world[map_x][map_y] == 1)
				hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		//printf("Wall Dist\n");
		if (side == 0)
			wall_dist = (map_x - data->ray->pos_x + (1 - step_x) / 2) / data->ray->ray_dir_x;
		else
			wall_dist = (map_y - data->ray->pos_y + (1 - step_y) / 2) / data->ray->ray_dir_y;
		//Calculate height of line to draw on screen
		line_height = (int)(data->screen_ht / wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		draw_start = -line_height / 2 + data->screen_ht / 2;
		if(draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + data->screen_ht / 2;
		if(draw_end >= data->screen_ht)
			draw_end = data->screen_ht - 1;
		//TTX - texturing calculations
		double	wall_hit; //calculate value of wallX where exactly the wall was hit
		int		tx_x;
		int		tx_y;
		double	step;
		double	tx_pos;
		int		lines;
		int		color;

		//tx_num = data->world[map_x][map_y] - 1; //1 subtracted from it so that texture 0 can be used!
		if (side == 0)
			wall_hit = data->ray->pos_y + wall_dist * data->ray->ray_dir_y;
		else
			wall_hit = data->ray->pos_x + wall_dist * data->ray->ray_dir_x;
		wall_hit -= floor((wall_hit));

		//x coordinate on the texture
		tx_x = (int)(wall_hit * (double)(TEXTR_WD));
		if(side == 0 && data->ray->ray_dir_x > 0)
			tx_x = TEXTR_WD - tx_x - 1;
		if(side == 1 && data->ray->ray_dir_y < 0)
			tx_x = TEXTR_WD - tx_x - 1;
		// How much to increase the texture coordinate per screen pixel
		step = 1.0 * TEXTR_HT / line_height;
		// Starting texture coordinate
		tx_pos = (draw_start - data->screen_ht / 2 + line_height / 2) * step;
		lines = draw_start;
		while (lines < draw_end)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			tx_y = (int)(tx_pos) & (TEXTR_HT - 1);
			tx_pos += step;
			if (side == 0)
				color = data->textures->addr[0][TEXTR_HT * tx_y + tx_x];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = data->textures->addr[1][TEXTR_HT * tx_y + tx_x];
			buffer[lines][stripes] = color;
			lines++;
		}

		//draw the pixels of the stripe as a vertical line
		//put_stripes(data, stripes, draw_start, draw_end, color);
		stripes++;
	}
	//print_buffer(buffer, data);
	draw_buffer(buffer, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	clear_buffer(buffer, data);
	return (1);
}

int		render_next_frame(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img->img);
	data->img->img = mlx_new_image(data->mlx, data->screen_wd, data->screen_ht);
	cast_img(data);
	return (1);
}

void	move_up(t_ray *ray, int world[WORLD_WD][WORLD_HT])
{
	if(world[(int)(ray->pos_x + ray->dir_x * ray->ms)][(int)(ray->pos_y)] == 0)
		ray->pos_x += ray->dir_x * ray->ms;
	if(world[(int)(ray->pos_x)][(int)(ray->pos_y + ray->dir_y * ray->ms)] == 0)
		ray->pos_y += ray->dir_y * ray->ms;
}

void	move_down(t_ray *ray, int world[WORLD_WD][WORLD_HT])
{
	if(world[(int)(ray->pos_x - ray->dir_x * ray->ms)][(int)(ray->pos_y)] == 0)
		ray->pos_x -= ray->dir_x * ray->ms;
	if(world[(int)(ray->pos_x)][(int)(ray->pos_y - ray->dir_y * ray->ms)] == 0)
		ray->pos_y -= ray->dir_y * ray->ms;
}

void	move_left(t_ray *ray)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = ray->dir_x;
	ray->dir_x = ray->dir_x * cos(ray->rs) - ray->dir_y * sin(ray->rs);
	ray->dir_y = old_dir_x * sin(ray->rs) + ray->dir_y * cos(ray->rs);
	old_plane_x = ray->plane_x;
	ray->plane_x = ray->plane_x * cos(ray->rs) - ray->plane_y * sin(ray->rs);
	ray->plane_y = old_plane_x * sin(ray->rs) + ray->plane_y * cos(ray->rs);
}

void	move_right(t_ray *ray)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = ray->dir_x;
	ray->dir_x = ray->dir_x * cos(-ray->rs) - ray->dir_y * sin(-ray->rs);
	ray->dir_y = old_dir_x * sin(-ray->rs) + ray->dir_y * cos(-ray->rs);
	old_plane_x = ray->plane_x;
	ray->plane_x = ray->plane_x * cos(-ray->rs) - ray->plane_y * sin(-ray->rs);
	ray->plane_y = old_plane_x * sin(-ray->rs) + ray->plane_y * cos(-ray->rs);
}

int		key_press(int keysym, t_data *data)
{
	if (keysym == XK_w)
	{
		move_up(data->ray, data->world);
		printf("You moved forward\n");
	}
	if (keysym == XK_s)
	{
		move_down(data->ray, data->world);
		printf("You moved backward\n");
	}
	if (keysym == XK_a)
	{
		move_left(data->ray);
		printf("You moved left\n");
	}
	if (keysym == XK_d)
	{
		move_right(data->ray);
		printf("You moved right\n");
	}
	if (keysym == XK_Left)
	{
		printf("You moved cam left\n");
	}
	if (keysym == XK_Right)
	{
		//both camera direction and camera plane must be rotated
		printf("You moved cam right\n");
	}
	if (keysym == XK_w || keysym == XK_s || keysym == XK_a || keysym == XK_d)
		render_next_frame(data);
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_loop_end(data->mlx);
	}
	return (1);
}

int		handle_no_event()
{
	return (1);
}

void init_texture_elements(t_textures *textures)
{
	textures->img = (void **)malloc(sizeof(void *) * 4);
	textures->bpp = (int *)malloc(sizeof(int) * 4);
	textures->line_len = (int *)malloc(sizeof(int) * 4);
	textures->endian = (int *)malloc(sizeof(int) * 4);
	textures->addr = (int **)malloc(sizeof(int *) * 4);
	textures->width = (int *)malloc(sizeof(int) * 4);
	textures->height = (int *)malloc(sizeof(int) * 4);
}

int load_textures(t_data *data, t_textures *textures)
{
	int x;

	textures->file_paths = (char **)malloc(sizeof(char *) * 5);
	textures->file_paths[0] = "./textures/colorstone.xpm";
	textures->file_paths[1] = "./textures/redbrick.xpm";
	textures->file_paths[2] = "./textures/greystone.xpm";
	textures->file_paths[3] = "./textures/wood.xpm";
	textures->file_paths[4] = 0;
	init_texture_elements(data->textures);
	x = 0;
	while (x < 4)
	{
		textures->img[x] = mlx_xpm_file_to_image(
				data->mlx, textures->file_paths[x], &textures->width[x], &textures->height[x]);
		printf("After img x - %d\n", x);
		textures->addr[x] = (int *)mlx_get_data_addr(textures->img[x], &textures->bpp[x], &textures->line_len[x], &textures->endian[x]);
		printf("After addr x - %d\n", x);
		//mlx_put_image_to_window(data->mlx, data->win, data->textures->img[x], x * 64, x * 64);
		x++;
	}
	printf("While loop ended\n");
}

int init_textures(t_data *data)
{
	data->textures = malloc(sizeof(t_textures));
	load_textures(data, data->textures);
}

int main(void)
{
	int  world[WORLD_WD][WORLD_HT] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	t_data *data;
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (-1);
	init_window(data);
	init_array(world, data->world);
	//print_array(data->world);
	init_img(data);
	init_ray(data);
	init_textures(data);
	render_next_frame(data);
	mlx_loop_hook(data->mlx, &handle_no_event, &data);
	mlx_hook(data->win, KeyPress, KeyPressMask, &key_press, data);
	mlx_loop(data->mlx);
	mlx_destroy_display(data->mlx);
	free(data->ray);
	free(data->img);
	free(data->mlx);
}
