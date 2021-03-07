#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct s_config {
	int				res_x;
	int				res_y;
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
	double			init_dir_x;
	double			init_dir_y;
	double			init_plane_x;
	double			init_plane_y;
	double			init_pos_x;
	double			init_pos_y;
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
	int			map_x;
	int			map_y;
	double		delta_dx;
	double		delta_dy;
	double		side_dx;
	double		side_dy;
	double		step_x;
	double		step_y;
	double		wall_dist;
	double		wall_hit;
	int			side;
	int			hit;
	int			step;
	int			line_h;
	int			start;
	int			end;
	int			tx_x;
	int			tx_y;
	double		tx_pos;
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
	int			save;
	t_ray		*ray;
	t_img		*img;
	t_img		**textures;
	t_input		*inputs;
	t_sprite	*sprite;
	t_config	*config;
}               t_data;

#endif
