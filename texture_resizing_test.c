#include <Tk/X11/X.h>
#include <stdlib.h>

#include "minilibx/mlx.h"

typedef struct s_mlx
{
	void		*mlx;
	void		*src_win;
	void		*dst_win;
	void		*src_img;
	void		*dst_img;
}	t_mlx;

int	exit_game(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->src_img);
	mlx_destroy_image(mlx->mlx, mlx->dst_img);
	mlx_destroy_window(mlx->mlx, mlx->src_win);
	mlx_destroy_window(mlx->mlx, mlx->dst_win);
	exit(0);
}

int	main()
{
	t_mlx		mlx;
	int			tmp;
	const int	dst_size = 1080;
	const int	src_size = 100;
	mlx.mlx = mlx_init();
	mlx.src_win = mlx_new_window(mlx.mlx, src_size, src_size, "Source");
	mlx.dst_win = mlx_new_window(mlx.mlx, dst_size, dst_size, "Result");
	mlx.src_img = mlx_xpm_file_to_image(mlx.mlx, "textures/vertical.xpm", &tmp, &tmp);
	mlx.dst_img = mlx_new_image(mlx.mlx, dst_size, dst_size);
	int			*src_buff = (int *)mlx_get_data_addr(mlx.src_img, &tmp, &tmp, &tmp);
	int			*dst_buff = (int *)mlx_get_data_addr(mlx.dst_img, &tmp, &tmp, &tmp);
	for (int x = 0; x < dst_size; x += 1)
	{
		for (int y = 0; y < dst_size; y += 1)
		{
			dst_buff[dst_size * y + x] = src_buff[src_size * src_size * y / dst_size + x * src_size / dst_size];
		}
	}
	mlx_put_image_to_window(mlx.mlx, mlx.dst_win, mlx.dst_img, 0, 0);
	mlx_put_image_to_window(mlx.mlx, mlx.src_win, mlx.src_img, 0, 0);
	mlx_hook(mlx.src_win, DestroyNotify, 0, exit_game, &mlx);
	mlx_hook(mlx.dst_win, DestroyNotify, 0, exit_game, &mlx);
	mlx_loop(mlx.mlx);
}
