/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:23:49 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/07/22 17:44:56 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include "../get_next/get_next_line.h"
# include <math.h>
# include "../minilibx/mlx.h"

# define NUM_RAYS 900
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

typedef struct s_ray
{
	float		planex;
	float		planey;
	float		deltadistx;
	float		deltadisty;
	int			stepx;
	int			stepy;
	float		sidedistx;
	float		sidedisty;
	int			side;
	float		perpwalldist;
	int			lineheight;
	int			drawstart;
	int			drawend;
	float		camerax;
	float		raydirx;
	float		raydiry;
	int			mapx;
	int			mapy;
}	t_ray;

typedef struct s_line
{
	double	angle;
	int		offset_x;
	int		offset_y;
	int		len;
	int		color;
}	t_line;

typedef struct s_maps
{
	int		width;
	int		hight;
	int		no;
	int		se;
	int		we;
	int		ea;
	int		f;
	int		c;
	int		fcolor;
	int		ccolor;
	void	*ntexture;
	void	*stexture;
	void	*wtexture;
	void	*etexture;
}	t_maps;

typedef struct s_img
{
	void	*img;
	int		bits;
	int		size_line;
	int		endian;
	char	*p;
	void	*miniimg;
	int		minibits;
	int		minisize_line;
	int		miniendian;
	char	*minip;
}	t_img;

typedef struct s_player
{
	float	x;
	float	y;
	int		radious;
	float	move_speed;
	float	move_step;
	float	rotation_angle;
	int		turndaraction;
	int		walkdaraction;
	float	rotation_speed;
	char	rederaction;
	int		tab[500];
	float	dirx;
	float	diry;
}	t_player;

typedef struct s_game
{
	char		*map_name;
	char		**map;
	t_maps		*ply_map;
	t_player	*player;
	t_line		*line;
	void		*win;
	void		*mlx;
	t_ray		*ray;
	t_img		t;
	float		rayangle;
	uint32_t	*textures;
	uint32_t	tex_x;
	uint32_t	tex_y;
	float		step;
	float		tex_pos;
	char		*color_ptr;
	int			tbits;
	int			tsize_line;
	double		wallx;
	int			tendian;
	int			door;
	void		*doortex;
}	t_game;

void	ft_error_exit(char *str);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(char *str, char c);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_right(t_game *game);
void	move_left(t_game *game);
void	count_w_h(t_game *game);
void	ray_casting(t_game *game);
void	twodfree(char **table);
void	initializedata(char **av, t_game *data);
void	check_map(char **str, t_game *game);
int		check_map_name(char *str);
char	**read_map(char *name);
void	fix_map(t_game *game);
void	rotate_right(t_game *game);
void	rotate_left(t_game *game);
void	checkelement(t_game *game);
char	*ft_strtrim(char *s1, char c);
int		ft_rgb_to_hex(int r, int g, int b);
int		ft_atoi(char *str);
void	getplayerposition(t_game *game);
void	getcolorfromimg(t_game *game);
void	getplayerchars(t_game *game, int i, int j, int *count);
void	getfloorcolor(char **colors, t_game *game);
void	getceillingcolor(char **colors, t_game *game);
char	*gettype(char *str);
void	getimgpath(t_game *game, char *type, char *str, int lol);
void	draw_minimap(t_game *game);
int		key_released(int key, t_game *game);
int		key_pressed(int key, t_game *game);
int		get_lenght(char **table);
void	fill_table(char **table, char **new, int tmp);
char	**makemaprect(t_game *game);
void	get_side_dist(t_game *game, t_ray *r);
void	fill_image(t_game *game, int i, int wallStart, int wallEnd);
#endif
