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
# include "../mlx_linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
#define WORLD_WD 24
#define WORLD_HT 24
#define TEXTR_WD 64
#define TEXTR_HT 64
#define C_COLOR 0X00FFF89B
#define F_COLOR 0X00FFC99B

void	handle_sprites(t_data *data, t_ray *ray, t_sprite *sprite);
void	bubble_sort_with_order(double *array, int *order, int size);

#endif
