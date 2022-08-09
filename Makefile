NAME = cub3d
BNAME = cub3d_bonus
CC = gcc

CFLAGS = -Wall -Werror -Wextra 

SRCS = main.c libftTools/libfttools.c libftTools/tools.c get_next/get_next_line.c \
	get_next/get_next_line_utils.c libftTools/ft_split.c mandatory/src/move_player.c \
	mandatory/src/initializeAll.c mandatory/src/parseMap.c mandatory/src/raycasting.c \
	libftTools/ft_strtrim.c libftTools/libfttools2.c mandatory/src/parseMap2.c mandatory/src/sometools.c \
	mandatory/src/moveUpDown.c mandatory/src/parseMap3.c mandatory/src/rc_tools.c \

BSRC = bonus/main_bonus.c libftTools/libfttools.c libftTools/tools.c get_next/get_next_line.c \
	get_next/get_next_line_utils.c libftTools/ft_split.c bonus/src_bonus/move_player_bonus.c \
	bonus/src_bonus/initializeall_bonus.c bonus/src_bonus/parsemap_bonus.c bonus/src_bonus/raycasting_bonus.c \
	libftTools/ft_strtrim.c libftTools/libfttools2.c bonus/src_bonus/parsemap2_bonus.c bonus/src_bonus/draw_minimap.c \
	bonus/src_bonus/parseMap3_bonus.c bonus/src_bonus/moveUpDown_bonus.c bonus/src_bonus/sometools_bonus.c \
	bonus/src_bonus/rc_tools_bonus.c bonus/src_bonus/check_line.c\

OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C minilibx
	mv	minilibx/libmlx.dylib .
	$(CC) $(CFLAGS) $(OBJS) libmlx.dylib -o $(NAME)

bonus : $(BNAME)
$(BNAME) : $(BOBJS)
	make -C minilibx
	mv	minilibx/libmlx.dylib .
	$(CC) $(CFLAGS) $(BOBJS) libmlx.dylib -o $(BNAME)

clean:
	make -C minilibx clean
	rm -f $(OBJS)
	rm -f $(BOBJS)

fclean: clean
	rm -rf libmlx.dylib
	rm -f $(NAME)
	rm -f $(BNAME)

re : fclean all
