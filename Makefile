NAME = cub3D

SRCS = mvp.c

OBJS = $(SRCS:.c=.o)

HEADERS = includes

MLX_REQ_LN = -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz

MLX_REQ_OSX = -Lmlx_osx -lmlx -framework OpenGL -framework AppKit

CC = gcc

CFLAGS = -Wall -Wextra

#LIB = -L./libft/ -lft

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(MLX_REQ_OSX)
	#	$(CC) -o $(NAME) $(OBJS) $(MLX_REQ_LN)
#		$(MAKE) -C ./libft
#		cp libft/libft.a ./$(NAME)
#		ar rcs $@ $^

%.o : %.c
		$(CC) ${CFLAGS} -I ${HEADERS} -Imlx_osx  -o $@ -c $<
		#$(CC) ${CFLAGS} -I ${HEADERS} -Imlx_linux -O3  -o $@ -c $<

clean :
#		$(MAKE) clean -C ./libft
		rm -f $(OBJS)

fclean : clean
#		 $(MAKE) fclean -C ./libft
		 rm -f $(NAME)

re : fclean all
