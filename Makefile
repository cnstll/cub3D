NAME = cub3D

SRCS = srcs/raycasting.c \
       srcs/sprite_casting.c\
       srcs/sprite_sorter.c \
		utils/utils_1.c \
		utils/utils_2.c \
		utils/utils_3.c \
		extract_map.c

OBJS = $(SRCS:.c=.o)

HEADERS = includes

MLX_REQ_LN = -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm

MLX_REQ_OSX = -Lmlx_osx -lmlx -framework OpenGL -framework AppKit

CC = gcc

CFLAGS = -Wall -Wextra -g

#LIB = -L./libft/ -lft

all : $(NAME)

$(NAME) : $(OBJS)
	#	$(CC) -o $(NAME) $(OBJS) $(MLX_REQ_OSX)
		$(CC) -o $(NAME) $(OBJS) $(MLX_REQ_LN)
#		$(MAKE) -C ./libft
#		cp libft/libft.a ./$(NAME)
#		ar rcs $@ $^

%.o : %.c
		#$(CC) ${CFLAGS} -I ${HEADERS} -Imlx_osx  -o $@ -c $<
		$(CC) ${CFLAGS} -I ${HEADERS} -Imlx_linux -o $@ -c $<

clean :
#		$(MAKE) clean -C ./libft
		rm -f $(OBJS)

fclean : clean
#		 $(MAKE) fclean -C ./libft
		 rm -f $(NAME)

re : fclean all
