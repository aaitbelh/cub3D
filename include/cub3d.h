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

typedef struct s_ray
{
	float	rayAngle;
	float	horzHitX;
	float	horzHitY;
	float	vertHitX;
	float	vertHitY;
	int		wasHitVert;
	int		wasHitHorz;
	int		isRayFacingUp;
	int		isRayFacingDown;
	int		isRayFacingLeft;
	int		isRayFacingRight;
	float	xstep;
	float	ystep;
	float	hDistance;
	float	vDistance;
	float	HitDistance;
	float	sliceHeight;
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
	int width;
	int hight;
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
	int tab[500];
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
	void		*cube;
	void		*cyrcle;
	void		*background;
	t_ray		*rays;
	float		rayangle;
	float		P_D;
	t_img		t;
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
void	raycasting(t_game *game);
int		mapHasWallAt(t_game *game, float x, float y);
void	drawRay(t_game *game,float D);
void	TwoDfree(char **table);
void	initializeData(int ac, char **av, t_game *data);
void	check_map(char **str, t_game *game);
int		check_map_name(char *str);
char	**read_map(char *name);
void	fix_map(t_game *game);
#endif