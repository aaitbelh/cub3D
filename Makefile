NAME = cub3d

CC = gcc


CFLAGS = -g -fsanitize=address
XFLACGS = -lmlx -framework OpenGL -framework Appkit


SRCS = main.c src/libfttools.c src/tools.c get_next/get_next_line.c get_next/get_next_line_utils.c src/ft_split.c src/move_player.c raycasting.c src/initializeAll.c src/parseMap.c src/libfttools2.c src/ft_strtrim.c

OBJS = $(SRCS:.c=.o)

USER  = aaitbelh


all : $(NAME)
$(NAME) : $(OBJS)
	# make -C minilibx
	# mv minilibx/libmlx.dylib .
	$(CC) $(CFLAGS) $(OBJS) $(XFLACGS)  -o $(NAME)

clean:
	make -C minilibx clean
	rm -f $(OBJS) libmlx.dylib

fclean: clean
	rm -f $(NAME)

re : fclean all
