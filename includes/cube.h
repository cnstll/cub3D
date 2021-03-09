#ifndef CUBE_H
#define CUBE_H

# include "./structures.h"
# include "./bmp.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include <math.h>
# include "../mlx_linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# define  READ_SIZE 64

void	handle_sprites(t_data *data, t_ray *ray, t_sprite *sprite);
void	bubble_sort_with_order(double *array, int *order, int size);
void	bubble_sort(t_sprite *sprite, double *array, int size);
char	*ft_strdup_till_char(char *s, char c, int start);
int		c_in_s(char c, char *s);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin_free(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
void	free_2d_string(char **s);
void	free_2d_array(int **array, int num_lines);
int		**malloc_2d_array(int **array, int size, int lines);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
char	*ft_str_append(char *s, char c);
int		ft_lite_atoi(const char *s);
char	**ft_lite_split(char *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		play(t_data *data);
int		save(t_data *data);
void	calculate_textures(t_data *data, t_ray *ray, t_img **textures, int s);
void	calculate_wall_dist(t_ray *ray, t_data *data);
void	diff_analysis(t_ray *ray, int **world);
void	ray_step_and_side(t_ray *ray);
void    ray_initiation(t_ray *ray, int stripes, int max_stripes);
int		clear_buffer(int **buffer, t_data *data);
int		draw_buffer(int **buffer, t_data *data);
int		init_inputs(t_data *data);
int		init_map(t_data *data);
int		init_textures(t_data *data);
int		init_ray(t_data *data);
int		init_img(t_data *data);
int		init_buffer(t_data *data);
int		init_mlx_window(t_data *data);
void	free_and_destroy_save(t_data *data);
void	free_and_destroy_play(t_data *data);
void	move_up(t_ray *ray, int **world);
void	move_down(t_ray *ray, int **world);
void	move_left(t_ray *ray, int **world);
void	move_right(t_ray *ray, int **world);
void	look_left(t_ray *ray);
void	look_right(t_ray *ray);
int		clic_to_close(int clic, t_data *data);
int		handle_player_move(t_data *data);
int		any_key_pressed(t_input *inputs);
int		key_press(int keysym, t_data *data);
int		key_release(int keysym, t_data *data);
int		render_next_frame(t_data *data);
int		cast_img(t_data *data, t_ray *ray);
int		map_max_height(char **map, int start);
int		map_max_width(char **map, int start);
char	*file_to_str(char *path_file);
int		check_res(char *p, int start);
int		copy_res(char *p, t_config *config, int start);
int		check_color(char *p, int start);
int		copy_color(char *p, t_config *config, int start);
void	parse_param_line(char *p, t_config *config);
unsigned long	rgb_to_hex(int r, int g, int b);
int		valid_elements_pair(char e1, char e2);
int		check_path(char *p, int start);
int		copy_path(char *p, t_config *config, int start);
int		check_parameters(t_config *config, int ret);
int		check_if_map(char *line, int num_line, t_config *config);
void	init_player(char dir, int x, int y, t_config *config);
void	init_player_dir(t_config *config, double rot);
void	init_config(t_data *data);
void	destroy_config(t_config *config);
void	error_handler(int error);
int		extract_config_elements(t_data *data, char *path_file);


#endif
