NAME = cub3D

SRCS = srcs/raycasting.c \
		srcs/sprite_casting.c\
		srcs/sprite_sorter.c \
		srcs/extract_map.c \
		srcs/buffer_handler.c \
		srcs/destroyer.c \
		srcs/init_sprites.c \
		srcs/init_struct.c \
		srcs/init_textures.c \
		srcs/key_handler.c \
		srcs/player_move.c \
		srcs/player_move2.c \
		utils/utils_1.c \
		utils/utils_2.c \
		utils/utils_3.c

OBJS = $(SRCS:.c=.o)

HEADERS = includes

MLX_REQ_LN = -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm

CC = gcc

CFLAGS = -Wall -Wextra -g

#LIB = -L./libft/ -lft

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(MLX_REQ_LN)
#		$(MAKE) -C ./libft
#		cp libft/libft.a ./$(NAME)
#		ar rcs $@ $^

%.o : %.c
		$(CC) ${CFLAGS} -I ${HEADERS} -Imlx_linux -o $@ -c $<

clean :
#		$(MAKE) clean -C ./libft
		rm -f $(OBJS)

fclean : clean
#		 $(MAKE) fclean -C ./libft
		 rm -f $(NAME)

re : fclean all
