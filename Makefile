NAME = cub3d

CC = gcc

CFLAGS = -g -fsanitize=address -Wall -Werror -Wextra

SRCS = main.c src/libfttools.c src/tools.c get_next/get_next_line.c get_next/get_next_line_utils.c src/ft_split.c src/move_player.c src/initializeAll.c src/parseMap.c raycasting.c src/ft_strtrim.c src/libfttools2.c src/parseMap2.c

OBJS = $(SRCS:.c=.o)

USER  = aaitbelh

all : $(NAME)

$(NAME) : $(OBJS)
	make -C minilibx
	mv minilibx/libmlx.dylib .
	$(CC) $(CFLAGS)  $(OBJS) libmlx.dylib -o $(NAME)

clean:
	make -C minilibx clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all
