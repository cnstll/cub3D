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
# define WORLD_WD 24
# define WORLD_HT 24
# define TEXTR_WD 64
# define TEXTR_HT 64
# define READ_SIZE 56
# define C_COLOR 0X00FFF89B
# define F_COLOR 0X00FFC99B
# define FIRST_L "RNSWESFC"
# define ALLOWED_SP " \t"
# define HEXA "0123456789ABCDEF"

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
#endif
