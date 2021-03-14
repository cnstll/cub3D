NAME = cub3D

SRCS = srcs/raycasting.c \
		utils/raycasting_utils.c \
		srcs/game.c \
		srcs/sprite_casting.c\
		srcs/sprite_sorter.c \
		srcs/buffer_handler.c \
		srcs/destroyer.c \
		srcs/init_sprites.c \
		srcs/init_struct.c \
		srcs/init_textures.c \
		srcs/key_handler.c \
		srcs/player_move.c \
		srcs/player_move2.c \
		srcs/error_handler.c \
		srcs/bmp.c \
		srcs/init_parsing.c \
		srcs/parsing_config.c \
		srcs/parsing_config2.c \
		srcs/parsing_config3.c \
		srcs/parsing_map.c \
		srcs/parsing_main.c \
		utils/utils_1.c \
		utils/utils_2.c \
		utils/utils_3.c \
		utils/utils_bmp.c \
		utils/utils_parsing.c

OBJS = $(SRCS:.c=.o)

HEADERS = includes

MLX_REQ_LN = -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

LIB = -L./libft/ -lft

all : $(NAME)

$(NAME) : $(OBJS)
		$(MAKE) -C ./libft
		$(CC) -o $(NAME) $(OBJS) $(MLX_REQ_LN) $(LIB)

%.o : %.c
		$(CC) ${CFLAGS} -I ${HEADERS} -Imlx_linux -o $@ -c $<

clean :
		$(MAKE) clean -C ./libft
		rm -f $(OBJS)

fclean : clean
		 $(MAKE) fclean -C ./libft
		 rm -f $(NAME)

re : fclean all
