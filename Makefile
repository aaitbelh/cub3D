NAME = cub3d

CC = gcc

CFLAGS = -g3 -fsanitize=address -Wall -Werror -Wextra

SRCS = main.c src/libfttools.c src/tools.c get_next/get_next_line.c get_next/get_next_line_utils.c src/ft_split.c src/move_player.c raycasting.c src/initializeAll.c src/parseMap.c

OBJS = $(SRCS:.c=.o)

USER  = aaitbelh

XFLAGS = -lm -lmlx -framework OpenGL -framework Appkit # MLX42/libmlx42.a -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -


all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) $(XFLAGS)  -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all
