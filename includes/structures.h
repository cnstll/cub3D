#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct	s_img {
	char		*file_paths;	
	void        *img;
	int			*addr;
	int         bpp;
	int         line_len;
	int         endian;
	int			width;
	int			height;
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

typedef struct  s_data {
	void		*mlx;
	void		*win;
	int			screen_ht;
	int			screen_wd;
	int			world[24][24];
	int			**buffer;
	t_ray		*ray;
	t_img		*img;
	t_img		**textures;
	t_input		**inputs;
}               t_data;

typedef struct	s_input {

	int			press;
	int			keysym;
}				t_input;
#endif
