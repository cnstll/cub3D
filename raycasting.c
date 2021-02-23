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
#define C_COLOR 0X00F9FF9D
#define F_COLOR 0X00F0FBE6

void	destroy_sprites(t_data *data)
{
	free(data->sprites);
	free(data->sp_buffer);
	free(data->sp_order);
	free(data->sp_distance);
}

void	free_all(t_data *data)
{
	free(data->mlx);
	free(data->ray);
	free(data->img);
	free(data->inputs);
	destroy_sprites(data);
	free(data);
}

int malloc_2d_array(int **array, int size, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		array[i] = (int *)malloc(size * sizeof(int));
		i++;
	}
	return (1);
}

int free_2d_array(int **array, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (1);
}

int		init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (-1);
	data->screen_wd = 640;
	data->screen_ht = 480;
	data->win =
		mlx_new_window(data->mlx, data->screen_wd, data->screen_ht, "cub3D");
	if (data->win == NULL)
		return (-1);
	data->buffer = (int **)malloc(sizeof(int *) * data->screen_ht);
	malloc_2d_array(data->buffer, data->screen_wd, data->screen_ht);
	return (1);
}

int		init_map(t_data *data)
{
	data->sprite = malloc(sizeof(t_sprite));
	data->sprite->num = 8;
	data->sprite->buffer = malloc(sizeof(double) * data->screen_wd);
	data->sprite->order = malloc(sizeof(int) * data->sprite->num);
	data->sprite->distance = malloc(sizeof(double) * data->sprite->num);
}

int		init_img(t_data *data)
{
	data->img = malloc(sizeof(t_img));
	data->img->img =
		mlx_new_image(data->mlx, data->screen_wd, data->screen_ht);
	data->img->addr = (int *)mlx_get_data_addr(
			data->img->img, &data->img->bpp, &data->img->line_len, &data->img->endian);
	return (1);
}

int		init_ray(t_data *data)
{
	data->ray = malloc(sizeof(t_ray));
	data->ray->pos_x = 18;
	data->ray->pos_y = 18;  //x and y start position
	data->ray->ms = 0.005;
	data->ray->rs = 0.005;
	data->ray->dir_x = -1;
	data->ray->dir_y = 0; //initial direction vector
	data->ray->plane_x = 0;
	data->ray->plane_y = 0.66; //the 2d raycaster version of camera plane
	return (1);
}

int load_textures(t_data *data, t_img **textures)
{
	int x;

	textures[0]->file_paths = "./textures/colorstone.xpm";
	textures[1]->file_paths = "./textures/redbrick.xpm";
	textures[2]->file_paths = "./textures/greystone.xpm";
	textures[3]->file_paths = "./textures/wood.xpm";
	textures[4]->file_paths = "./textures/pillar.xpm";
	x = 0;
	while (x < 5)
	{
		textures[x]->img = mlx_xpm_file_to_image(
				data->mlx, textures[x]->file_paths, &textures[x]->width, &textures[x]->height);
		textures[x]->addr = (int *)mlx_get_data_addr(
				textures[x]->img, &textures[x]->bpp, &textures[x]->line_len, &textures[x]->endian);
		x++;
	}
	return(1);
}

int init_textures(t_data *data)
{
	int x;

	x = 0;
	data->textures = malloc(sizeof(t_img *) * 5);
	while (x < 5)
	{
		data->textures[x] = malloc(sizeof(t_img));
		x++;
	}
	load_textures(data, data->textures);
	return (1);
}

int	init_sprites(t_data *data)
{
	data->sprite->sp = malloc(sizeof(t_sp) * data->sprite->num);
	data->sprite->sp[0] = (t_sp){21.5, 1.5, 4};
	data->sprite->sp[1] = (t_sp){15.5, 1.8, 4};
	data->sprite->sp[2] = (t_sp){16.0, 1.2, 4};
	data->sprite->sp[3] = (t_sp){16.2, 2.5, 4};
	data->sprite->sp[4] = (t_sp){3.5, 15.5, 4};
	data->sprite->sp[5] = (t_sp){9.5, 15.1, 4};
	data->sprite->sp[6] = (t_sp){10.5, 15.8, 4};
	data->sprite->sp[7] = (t_sp){11.5, 1.5, 4};
	return (1);
}

int	destroy_textures(t_data *data)
{
	int x;

	x = 0;
	while (x < 5)
	{
		mlx_destroy_image(data->mlx, data->textures[x]->img);
		x++;
	}
	x = 0;
	while (x < 5)
		free(data->textures[x++]);
	free(data->textures);
	return (1);
}

int	init_inputs(t_data *data)
{
	data->inputs = malloc(sizeof(t_input));
	data->inputs->key_w = 0;
	data->inputs->key_s = 0;
	data->inputs->key_a = 0;
	data->inputs->key_d = 0;
	data->inputs->key_left = 0;
	data->inputs->key_right = 0;
	data->inputs->key_esc = 0;
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
			buffer[y][x] = 0;
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

	x = 0;
	while (x < data->screen_wd)
	{
		y = 0;
		while(y < data->screen_ht)
		{
			printf("%d ",buffer[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	return (1);
}

int	put_ceilling(t_data *data, int stripes, int wall_top)
{
	int i;

	i = 0;
	while (i < wall_top - 1)
		data->buffer[i++][stripes] = C_COLOR;
	return (1);
}

int	put_floor(t_data *data, int stripes, int wall_bot)
{
	int i;

	i = wall_bot + 1;
	while (i < data->screen_ht)
		data->buffer[i++][stripes] = F_COLOR;
	return (1);
}

int bubble_sort(void *array, int size)
{
	int i;
	int	tmp;
	int	done;

	i = 0;
	done = 1;
	tmp = 0;
	while (done > 0)
	{
		while (i < size - 1)
		{
			tmp = array[i];
			if (array[i] < array[i + 1])
			{
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				done++;
			}
			else if (array[i] > array[i + 1])
				done--;
			i++;
		}
		i = 0;
	}
}

int	sort_sprites(t_ray *ray, t_sprite *sprite)
{
	int i;

	i = 0;
    while(i < sprite->num)
    {
		sprite->order[i] = i;
		sprite->distance[i] = ((ray->pos_x - sprite->sp[i]->x)
			* (ray->pos_x - sprite->sp[i]->x) + (ray->pos_y - sprite->sp[i]->y) 
			* (ray->pos_y - sprite->sp[i]->y));
		i++;
	}
	bubble_sort(sprite->distance, sprite->num);
}

int	put_sprites(t_data *data)
{
    //SPRITE CASTING
    //sort sprites from far to close
	int i;

	i = 0;
    while(i < data->sp_num)
    {
		data->sp_order[i] = i;
		data->sprites_info->distance[i] = ((data->ray->pos_x - data->sprites[i]->x) * (data->ray->pos_x - data->sprites[i]->x) + (data->ray->pos_y - data->sprites[i]->y) * (data->ray->pos_y - data->sprites[i]->y));
		i++;
	}
    sort_sprites(data->sp_order, data->sp_distance, data->sp_num);

    //after sorting the sprites, do the projection and draw them
    i = 0;
	while(i < data->sp_num)
    {
      //translate sprite position to relative to camera
      double spriteX = sprite[spriteOrder[i]].x - posX;
      double spriteY = sprite[spriteOrder[i]].y - posY;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication

      double transformX = invDet * (dirY * spriteX - dirX * spriteY);
      double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

      int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

      //calculate height of the sprite on screen
      int spriteHeight = abs(int(h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + h / 2;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + h / 2;
      if(drawEndY >= h) drawEndY = h - 1;

      //calculate width of the sprite
      int spriteWidth = abs( int (h / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= w) drawEndX = w - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * texHeight) / spriteHeight) / 256;
          Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
          if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
        }
      }
    }	
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
	stripes = 0;
	max_stripes = data->screen_wd;
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
			if (data->world[map_x][map_y] > 0)
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
		if(draw_end >= data->screen_ht || draw_end < 0)
			draw_end = data->screen_ht - 1;
		//TTX - texturing calculations
		double	wall_hit; //calculate value of wallX where exactly the wall was hit
		int		tx_x;
		int		tx_y;
		double	step;
		double	tx_pos;
		int		lines;
		int		color;

		if (side == 0)
			wall_hit = data->ray->pos_y + wall_dist * data->ray->ray_dir_y;
		else
			wall_hit = data->ray->pos_x + wall_dist * data->ray->ray_dir_x;
		wall_hit -= floor((wall_hit));

		tx_x = (int)(wall_hit * (double)(TEXTR_WD));
		if(side == 0 && data->ray->ray_dir_x > 0)
			tx_x = TEXTR_WD - tx_x - 1;
		if(side == 1 && data->ray->ray_dir_y < 0)
			tx_x = TEXTR_WD - tx_x - 1;
		step = 1.0 * TEXTR_HT / line_height;
		tx_pos = (draw_start - data->screen_ht / 2 + (line_height / 2)) * step;
		lines = draw_start;
		while (lines < draw_end)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			tx_y = (int)(tx_pos) & (TEXTR_HT - 1);
			tx_pos += step;
			if (side == 0 && data->ray->ray_dir_x < 0)
				color = data->textures[0]->addr[TEXTR_WD * tx_y + tx_x];
			else if (side == 0 && data->ray->ray_dir_x >= 0)
				color = data->textures[1]->addr[TEXTR_WD * tx_y + tx_x];
			else if (side == 1 && data->ray->ray_dir_y < 0)
				color = data->textures[2]->addr[TEXTR_WD * tx_y + tx_x];
			else
				color = data->textures[3]->addr[TEXTR_WD * tx_y + tx_x];
			data->buffer[lines][stripes] = color;
			lines++;
		}
		put_ceilling(data, stripes, draw_start);
		put_floor(data, stripes, draw_end);
		//draw the pixels of the stripe as a vertical line
		//put_stripes(data, stripes, draw_start, draw_end, color);
		data->sp_buffer[stripes] = wall_dist;
		stripes++;
	}
	//print_buffer(buffer, data);
	put_sprites(t_data *data);
	draw_buffer(data->buffer, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	clear_buffer(data->buffer, data);
	return (1);
}

int		render_next_frame(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img->img);
	free(data->img);
	init_img(data);
	//data->img->img = mlx_new_image(data->mlx, data->screen_wd, data->screen_ht);
	//memcpy(data->img[0].addr, data->img[1].addr, data->img[1].line_len * WINDOW_HEIGHT);
	//	data->img->addr = (int *)mlx_get_data_addr(
	//data->img->img, &data->img->bpp, &data->img->line_len, &data->img->endian);
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

void	move_left(t_ray *ray, int world[WORLD_WD][WORLD_HT])
{
	if(world[(int)(ray->pos_x - ray->plane_x * ray->ms)][(int)(ray->pos_y)] == 0)
		ray->pos_x -= ray->plane_x * ray->ms;
	if(world[(int)(ray->pos_x)][(int)(ray->pos_y - ray->plane_y * ray->ms)] == 0)
		ray->pos_y -= ray->plane_y * ray->ms;
}

void	move_right(t_ray *ray, int world[WORLD_WD][WORLD_HT])
{
	if(world[(int)(ray->pos_x + ray->plane_x * ray->ms)][(int)(ray->pos_y)] == 0)
		ray->pos_x += ray->plane_x * ray->ms;
	if(world[(int)(ray->pos_x)][(int)(ray->pos_y + ray->plane_y * ray->ms)] == 0)
		ray->pos_y += ray->plane_y * ray->ms;
}

void	look_left(t_ray *ray)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = ray->dir_x;
	ray->dir_x = ray->dir_x * cos(ray->rs) - ray->dir_y * sin(ray->rs);
	ray->dir_y = old_dir_x * sin(ray->rs) + ray->dir_y * cos(-ray->rs);
	old_plane_x = ray->plane_x;
	ray->plane_x = ray->plane_x * cos(ray->rs) - ray->plane_y * sin(ray->rs);
	ray->plane_y = old_plane_x * sin(ray->rs) + ray->plane_y * cos(ray->rs);
}

void	look_right(t_ray *ray)
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

int		key_release(int keysym, t_data *data)
{
	if (keysym == XK_w)
		data->inputs->key_w = 0;
	if (keysym == XK_s)
		data->inputs->key_s = 0;
	if (keysym == XK_a)
		data->inputs->key_a = 0;
	if (keysym == XK_d)
		data->inputs->key_d = 0;
	if (keysym == XK_Left)
		data->inputs->key_left = 0;
	if (keysym == XK_Right)
		data->inputs->key_right = 0;
	return (1);
}

int		key_press(int keysym, t_data *data)
{
	if (keysym == XK_w)
		data->inputs->key_w = 1;
	if (keysym == XK_s)
		data->inputs->key_s = 1;
	if (keysym == XK_a)
		data->inputs->key_a = 1;
	if (keysym == XK_d)
		data->inputs->key_d = 1;
	if (keysym == XK_Left)
		data->inputs->key_left = 1;
	if (keysym == XK_Right)
		data->inputs->key_right = 1;
	if (keysym == XK_Escape && data->win)
	{
		data->inputs->key_esc = 1;
		destroy_textures(data);
		free_2d_array(data->buffer, data->screen_ht);
		mlx_destroy_window(data->mlx, data->win);
		mlx_loop_end(data->mlx);
	}
	return (1);
}

int		handle_player_move(t_data *data)
{
	int	esc;

	esc = data->inputs->key_esc;
	if (data->inputs->key_w == 1 && esc < 1)
		move_up(data->ray, data->world);
	if (data->inputs->key_s == 1 && esc < 1)
		move_down(data->ray, data->world);
	if (data->inputs->key_a == 1 && esc < 1)
		move_left(data->ray, data->world);
	if (data->inputs->key_d == 1 && esc < 1)
		move_right(data->ray, data->world);
	if (data->inputs->key_left == 1 && esc < 1)
		look_left(data->ray);
	if (data->inputs->key_right == 1)
		look_right(data->ray);
	if (esc < 1)
		render_next_frame(data);
	return (1);
}


int main(void)
{
	int  world[WORLD_WD][WORLD_HT] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
	init_inputs(data);
	render_next_frame(data);
	mlx_hook(data->win, 2, 1L<<0, &key_press, data);
	mlx_hook(data->win, 3, 1L<<1, &key_release, data);
	mlx_loop_hook(data->mlx, &handle_player_move, data);
	mlx_loop(data->mlx);
	mlx_destroy_display(data->mlx);
	free_all(data);
	return (1);
}
