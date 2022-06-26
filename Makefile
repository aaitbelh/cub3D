NAME = cub3d

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS = main.c libftTools/libfttools.c libftTools/tools.c get_next/get_next_line.c \
	get_next/get_next_line_utils.c libftTools/ft_split.c mandatory/src/move_player.c \
	mandatory/src/initializeAll.c mandatory/src/parseMap.c mandatory/src/raycasting.c \
	libftTools/ft_strtrim.c libftTools/libfttools2.c mandatory/src/parseMap2.c \

OBJS = $(SRCS:.c=.o)


all : $(NAME)

$(NAME) : $(OBJS)
	make -C minilibx
	mv	minilibx/libmlx.dylib .
	$(CC) $(CFLAGS) $(OBJS) libmlx.dylib -o $(NAME)

clean:
	make -C minilibx clean
	rm -f $(OBJS)

fclean: clean
	rm -rf libmlx.dylib
	rm -f $(NAME)

re : fclean all
