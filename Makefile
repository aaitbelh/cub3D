NAME = cub3d

CC = gcc

MLX = libmlx.dylib

CFLAGS = -g -fsanitize=address -Wall -Werror -Wextra

SRCS = main.c src/libfttools.c src/tools.c get_next/get_next_line.c get_next/get_next_line_utils.c src/ft_split.c src/move_player.c raycasting.c src/initializeAll.c src/parseMap.c

OBJS = $(SRCS:.c=.o)

USER  = aaitbelh

XFLAGS = -lm -lmlx -framework OpenGL -framework Appkit


all : $(NAME)
$(NAME) : $(OBJS)
	make -C minilibx
	mv minilibx/$(MLX) .
	$(CC) $(CFLAGS) $(OBJS) $(XFLAGS) $(MLX) -o $(NAME)

clean:
	make -C minilibx clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all
