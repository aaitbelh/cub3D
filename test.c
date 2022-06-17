#include "include/cub3d.h"


typedef struct lol
{
	void *img;
	int b;
	int s;
	int e;
	char *p;
} t_lol;
void	put_pixel_in_image(t_lol *game, int i, int j, int color)
{
	char	*a;

	a = game->p + (j * game->s + i * (game->b / 8));
	*(unsigned int *)a = color;
}

int main()
{
	void *mlx;
	void *win;
	t_lol lol;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1000, 1000, "mlx");
	lol.img = mlx_new_image(mlx, 500, 500);

	lol.p = mlx_get_data_addr(lol.img, &lol.b, &lol.s, &lol.e);
	for(int c = 0; c < 500 ; c++)
	{
		for(int d = 0; d < 500 ; d++)
		{
			put_pixel_in_image(&lol, c, d, 0xFF0000);
		}

	}
	mlx_put_image_to_window(mlx, win, lol.img, 0, 0);
	mlx_loop(mlx);
}