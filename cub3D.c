/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:30:01 by mamazari          #+#    #+#             */
/*   Updated: 2024/09/26 16:02:58 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <fcntl.h>
#include <string.h>
#include <Tk/X11/X.h>
#include <sys/fcntl.h>

#include "minilibx/mlx.h"
#include "error/error.h"
#include "error/codes.h"
#include "game/game.h"
#include "c3d_math/c3d_math.h"
#include "game/config.h"

bool	test_level(t_game *game);

int	main(int argc, char **argv)
{
	static t_game	game = {.e = {0}};
	int				tmp;

	(void)argv;
	game.r.mlx = mlx_init();
	if (track(&game.e, "main")
		&& check_err(&game.e, game.r.mlx != NULL, MLX_INIT)
		&& check_err(&game.e, argc == 2, C3D_MAIN_INV_PARAM)
		&& test_level(&game))
	{
		game.r.win = mlx_new_window(game.r.mlx, WIN_WIDTH, WIN_HEIGHT,
				"cub3D");
		game.r.img = mlx_new_image(game.r.mlx, WIN_WIDTH, WIN_HEIGHT);
		if (check_err(&game.e, game.r.win != NULL, MLX_ALLOC)
			&& check_err(&game.e, game.r.img != NULL, MLX_ALLOC))
		{
			game.r.img_buff = (int *)mlx_get_data_addr(game.r.img, &tmp,
					&tmp, &tmp);
			mlx_do_key_autorepeaton(game.r.mlx);
			mlx_hook(game.r.win, KeyPress, 0, key_hook, &game);
			mlx_hook(game.r.win, DestroyNotify, 0, exit_game, &game);
			mlx_loop_hook(game.r.mlx, mouse_look, &game);
			mlx_mouse_move(game.r.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
			mlx_mouse_hide();
			render(&game);
			mlx_loop(game.r.mlx);
		}
	}
	print_trace(&game.e);
	return (game.e.error);
}

bool	test_level(t_game *game)
{
	t_texture	*texture;

	if (track(&game->e, "test_level") && create_mat(&game->map, 10, 6,
			&game->e))
	{
		memcpy(game->map.m[0], "1111111111", 10);
		memcpy(game->map.m[1], "1000000001", 10);
		memcpy(game->map.m[2], "1011111101", 10);
		memcpy(game->map.m[3], "1010000101", 10);
		memcpy(game->map.m[4], "1000000001", 10);
		memcpy(game->map.m[5], "1111111111", 10);
		game->ppos.x = 8.5f;
		game->ppos.y = 1.5f;
		game->prot.x = 0.0f;
		game->prot.y = 1.0f;
		game->cam.x = CAMERA_HALF_FOV_TAN;
		game->cam.y = 0.0f;
		game->r.ceil_color = 0x6e5020;
		game->r.floor_color = 0xa68444;
		texture = game->r.textures['1' - FIRST_MAP_SYMBOL];
		texture->img = mlx_xpm_file_to_image(game->r.mlx, "textures/backrooms.xpm", &texture->w, &texture->h);
		texture[1].img = mlx_xpm_file_to_image(game->r.mlx, "textures/chess.xpm", &texture->w, &texture->h);
		texture[2].img = mlx_xpm_file_to_image(game->r.mlx, "textures/pool.xpm", &texture->w, &texture->h);
		texture[3].img = mlx_xpm_file_to_image(game->r.mlx, "textures/tubes.xpm", &texture->w, &texture->h);
		untrack(&game->e);
	}
	return (game->map.m != NULL);
}
