#ifndef CUB3D_H
#define CUB3D_H


#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include "../get_next/get_next_line.h"
#include <math.h>

#include "../minilibx/mlx.h"

# define FOV_ANGLE 60 * (M_PI / 180)
# define NUM_RAYS 900
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

typedef struct s_ray
{
	float		planeX;
	float		planeY;
	float		deltaDistX;
	float		deltaDistY;
	int			stepX;
	int			stepY;
	float		sideDistX;
	float		sideDistY;
	int			side;
	float		perpWallDist;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	float		cameraX;
	float		rayDirX;
	float		rayDirY;
	int			mapX;
	int			mapY;
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
	int		NO;
	int		SE;
	int		WE;
	int		EA;
	int		F;
	int		C;
	int		Fcolor;
	int		Ccolor;
	void	*Ntexture;
	void	*Stexture;
	void	*Wtexture;
	void	*Etexture;
} t_maps;

typedef	struct s_img
{
	void	*img;
	int		bits;
	int		size_line;
	int		endian;
	char	*p;
}	t_img;


typedef struct s_player
{
	float x;
	float y;
	int radious;
	float move_speed;
	float move_step;
	float rotation_angle;
	int turndaraction;
	int walkdaraction;
	float rotation_speed;
	char rederaction;
	int tab[500];
	float		dirX;
	float		dirY;
} t_player;

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
	float		P_D;
	//--------------------
	uint32_t	*textures;
	uint32_t	texX;
	uint32_t	texY;
	float		step;
	float		texPos;
	char 		*colorPointer;
	int			tbits;
	int			tsize_line;
	int			tendian;
	
} t_game;

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
int		mapHasWallAt(t_game *game, float x, float y);
void	drawRay(t_game *game,float D);
void	TwoDfree(char **table);
void	initializeData(int ac, char **av, t_game *data);
void	check_map(char **str, t_game *game);
int		check_map_name(char *str);
char	**read_map(char *name);
void	fix_map(t_game *game);
void	rotate_right(t_game *game);
void 	rotate_left(t_game *game);
void	checkElement(t_game *game);
char	*ft_strtrim(char *s1, char c);
int		ft_rgb_to_hex(int r, int g, int b);
int		ft_atoi(char *str);
void	getPlayerPosition(t_game *game);
void	GetColorfromimg(t_game *game);
#endif