#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct s_config {
	char			*res_x;
	char			*res_y;
	char			*tx_no;
	char			*tx_so;
	char			*tx_ea;
	char			*tx_we;
	char			*tx_sprite;
	unsigned int	f_color;
	unsigned int	c_color;
	int				f_saved;
	int				c_saved;
	int				count_param;
	int				init_dir_x;
	int				init_dir_y;
	int				init_pos_x;
	int				init_pos_y;
}				t_config;

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

typedef struct	s_input {

	int			key_w;
	int			key_s;
	int			key_a;
	int			key_d;
	int			key_left;
	int			key_right;
	int			key_esc;
}				t_input;

typedef struct	s_sp {
	double		x;
	double		y;
	int			tx_num;
}				t_sp;

typedef struct	s_sprite {
	int			num;
	double		*buffer;
	int			*order;
	double		*distance;
	double		x;
	double		y;
	int			tx_x;
	int			tx_y;
	double		invert;
	double		transfo_x;
	double		transfo_y;
	int			start_x;
	int			end_x;
	int			start_y;
	int			end_y;
	int			screen_x;
	int			height;
	int			width;
	t_sp		*sp;
}				t_sprite;

typedef struct  s_data {
	void		*mlx;
	void		*win;
	int			screen_ht;
	int			screen_wd;
	int			**world;
	int			world_wd;
	int			world_ht;
	int			**buffer;
	t_ray		*ray;
	t_img		*img;
	t_img		**textures;
	t_input		*inputs;
	t_sprite	*sprite;
	t_config	*config;
}               t_data;

#endif
