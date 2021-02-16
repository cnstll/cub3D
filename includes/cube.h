#include "../mlx_linux/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#if defined __linux__  
	#include <X11/keysym.h>
	#include <X11/X.h>
#elif __APPLE__
	#define XK_Escape                        53
	#define XK_Left                          123
	#define XK_Right                         124
	#define XK_s                             1
	#define XK_a                             0
	#define XK_d                             2
	#define XK_w                             13
	#define KeyPressMask					(1L<<0)
	#define KeyPress							2
#endif
