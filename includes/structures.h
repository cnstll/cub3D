#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct	s_img {
	void        *img;
	char        *addr;
	int         bpp;
	int         line_len;
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
	double		rs;
	double		ms;
}				t_ray;

typedef struct	s_textures {
	int		width;
	int		height;
	char	**file_paths;	
	int		***img;
}				t_textures; 

typedef struct  s_data {
	void		*mlx;
	void		*win;
	int			screen_ht;
	int			screen_wd;
	int			world[WORLD_WD][WORLD_HT];
	t_ray		*ray;
	t_img		*img;
	t_textures	*textures;
}               t_data;
#endif
