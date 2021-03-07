#ifndef CUBE_H
#define CUBE_H

# include "./structures.h"
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
int		set_configuration(t_data *data);
void	calculate_textures(t_ray *ray, t_img **textures, int stripes);
void	calculate_wall_dist(t_ray *ray);
void	diff_analysis(t_ray *ray);
void	ray_step_and_side(t_ray *ray);
void    ray_initiation(t_ray *ray);
int		clear_buffer(int **buffer, t_data *data);
int		draw_buffer(int **buffer, t_data *data);
int		init_inputs(t_data *data);
int		init_map(t_data *data);
int		init_textures(t_data *data);
int		init_ray(t_data *data);
int		init_img(t_data *data);
int		init_buffer(t_data *data);
int		init_mlx_window(t_data *data);
void	free_and_destroy_all(t_data *data);
#endif
