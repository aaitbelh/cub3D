#include <string.h>
#include <stdio.h>
#include "minilibx/mlx.h"
#include <stdlib.h>
struct game
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*p;
	int		bits;
	int		size_line;
	int		endian;
};


// void	put_pixel_in_image(struct game *game, int i, int j, int color)
// {
// 	char	*a;

// 	a = game->t.p + (j * game->t.size_line + i * (game->t.bits / 8));
// 	*(unsigned int *)a = color;
// }

unsigned int getColor(struct game *game, int  i, int j)
{
	char *a;
	a = mlx_get_data_addr(game->img_ptr, &game->bits, &game->size_line, &game->endian);
	a += j * game->size_line + i * (game->bits / 8);
	unsigned int color;
	color = *(unsigned int *)a;
	return (color);
}



int main()
{
	struct game game;
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, 1800, 900, "mlx window");
	game.img_ptr = mlx_png_file_to_image(game.mlx_ptr, "walls1.png", &game.bits, &game.size_line);
	unsigned int color = getColor(&game, 0, 0);
	printf("%d\n", color);
	for(int i = 0; i < 64; i++)
	{
		for(int j = 0; j < 64; j++)
		{
			for(int s = 0 ; s <  2; s++)
			{
				color = getColor(&game, i, j);
				for (int l = 0 ; l < 2 ; l++)
				{
					mlx_pixel_put(game.mlx_ptr, game.win_ptr, i * 2 + s, j * 2 + l, color);
				}
				
			}
		}
	}
	mlx_loop(game.mlx_ptr);
}