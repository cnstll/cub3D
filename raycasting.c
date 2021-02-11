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

typedef struct	s_img {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
	int			width;
	int			height;
	double		time;
	double		old_time;
}				t_img;	

typedef struct s_ray {

	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
}				t_ray;

typedef struct  s_data {
	void		*mlx;
	void		*win;
	int			screen_ht;
	int			screen_wd;
	int			world[WORLD_WD][WORLD_HT];
	t_ray		*ray;
	t_img		*img;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->img->addr + (y * data->img->line_length + x * (data->img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		init_window(t_data *data)
{
	data->mlx = mlx_init();
	data->screen_wd = 640;
	data->screen_ht = 480;
	data->win = mlx_new_window(data->mlx, data->screen_wd, data->screen_ht, "cub3D");
	return (1);
}

int		init_img(t_data *data)
{
	t_img *img;

	img = malloc(sizeof(t_img));
	img->time = 0; //time of current frame
	img->old_time = 0; //time of previous fram
	img->img = mlx_new_image(data->mlx, data->screen_wd, data->screen_ht);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	data->img = img;
	return (1);
}

int		init_ray(t_data *data)
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	ray->pos_x = 4;
	ray->pos_y = 4;  //x and y start position
	ray->dir_x = -1; 
	ray->dir_y = 0; //initial direction vector
	ray->plane_x = 0; 
	ray->plane_y = 1; //the 2d raycaster version of camera plane
	data->ray = ray;
	return (1);
}

/*int put_textured_img(t_data *data)
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
  }
  }*/

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

int put_stripes(t_data *data, int x, int start, int end, int color)
{
	int i;

	i = start;
	while (i <= end)
	{
		my_mlx_pixel_put(data, x, i, color);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (1);
}

int render_next_frame(t_data *data)
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
	stripes = 0;
	max_stripes = 640;
	while (stripes < max_stripes)
	{
		data->ray->camera_x = 2 * stripes / (double)(max_stripes) - 1; //x-coordinate in camera space
		data->ray->ray_dir_x = data->ray->dir_x + data->ray->plane_x * data->ray->camera_x;
		data->ray->ray_dir_y = data->ray->dir_y + data->ray->plane_y * data->ray->camera_x;

		//which box of the map we're in
		map_x = (int)(data->ray->pos_x);
		map_y = (int)(data->ray->pos_y);

		//length of ray from one x or y-side to next x or y-side
		delta_dist_x = fabs(1 / data->ray->ray_dir_x);
		delta_dist_y = fabs(1 / data->ray->ray_dir_y);
		//was there a wall hit?
		hit = 0;
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
		//ADAPT THIS CODE WITH MLX
		//choose wall color
		int color;
		if(data->world[map_x][map_y] == 1)
			color = 0x00FF0000; 

		//give x and y sides different brightness
		if (side == 1) 
			color = 0x0000FF00;

		//draw the pixels of the stripe as a vertical line
		put_stripes(data, stripes, draw_start, draw_end, color);
		stripes++;
	}
	return (1);
}

int            key_hook(int keycode, t_data *data)
{
	if (keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2)
	{
		printf("img destroyed !\n");
	}
	if (keycode == 13)
	{
		if(data->world[(int)(data->ray->pos_x + data->ray->dir_x)][(int)(data->ray->pos_y)] == 0)
			data->ray->pos_x += data->ray->dir_x;
		if(data->world[(int)(data->ray->pos_x)][(int)(data->ray->pos_y + data->ray->dir_y)] == 0) 
			data->ray->pos_y += data->ray->dir_y;
		render_next_frame(data);
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
	return (1);
}

int extract_map()
{
	int fd;

	fd = 0;
	fd = open("./map_test.cub", O_RDONLY);
	read(fd, buf, read_size);

	close(fd);
}

int main(void)
{
	int  world[WORLD_WD][WORLD_WD] = {	
		{1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
	init_window(data);
	init_array(world, data->world);
	//print_array(data->world);
	init_ray(data);
	init_img(data);
	render_next_frame(data);
	mlx_key_hook(data->win, key_hook, &data);	
	mlx_loop(data->mlx);
}
