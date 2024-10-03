/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:30:01 by mamazari          #+#    #+#             */
/*   Updated: 2024/10/03 14:06:00 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	free_game(t_render *r, t_mat *map, t_mat *states);

int	main(int argc, char **argv)
{
	static t_game	game = {.e = {0}, .r = {0}};
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
	free_game(&game.r, &game.map, &game.states);
	return (game.e.error);
}

bool	test_level(t_game *game)
{
	if (track(&game->e, "test_level") && create_mat(&game->map, 5, 5,
			&game->e))
	{
		memcpy(game->map.m[0], "11111", 5);
		memcpy(game->map.m[1], "10001", 5);
		memcpy(game->map.m[2], "10001", 5);
		memcpy(game->map.m[3], "10001", 5);
		memcpy(game->map.m[4], "11111", 5);
		game->ppos.x = 2.5f;
		game->ppos.y = 2.5f;
		game->prot.x = 0.0f;
		game->prot.y = 1.0f;
		game->cam.x = CAMERA_HALF_FOV_TAN;
		game->cam.y = 0.0f;
		game->r.ceil_color = 0x6e5020;
		game->r.floor_color = 0xa68444;
		game->r.wall_sides[0].img = mlx_xpm_file_to_image(game->r.mlx,
				"textures/backrooms.xpm", &game->r.wall_sides[0].w,
				&game->r.wall_sides[0].h);
		game->r.wall_sides[1].img = mlx_xpm_file_to_image(game->r.mlx,
				"textures/pool.xpm", &game->r.wall_sides[1].w,
				&game->r.wall_sides[1].h);
		game->r.wall_sides[2].img = mlx_xpm_file_to_image(game->r.mlx,
				"textures/tubes.xpm", &game->r.wall_sides[2].w,
				&game->r.wall_sides[2].h);
		game->r.wall_sides[3].img = mlx_xpm_file_to_image(game->r.mlx,
				"textures/vertical.xpm", &game->r.wall_sides[3].w,
				&game->r.wall_sides[3].h);
		if (check_err(&game->e, game->r.wall_sides[0].img != NULL, MLX_ALLOC)
			&& check_err(&game->e, game->r.wall_sides[1].img != NULL, MLX_ALLOC)
			&& check_err(&game->e, game->r.wall_sides[2].img != NULL, MLX_ALLOC)
			&& check_err(&game->e, game->r.wall_sides[3].img != NULL,
				MLX_ALLOC))
			untrack(&game->e);
	}
	return (!game->e.error);
}

void	free_game(t_render *r, t_mat *map, t_mat *states)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (r->wall_sides[i].img)
			mlx_destroy_image(r->mlx, r->wall_sides[i].img);
		i += 1;
	}
	i = 0;
	while (i < DOOR_FRAMES_COUNT)
	{
		if (r->door_frames[i].img)
			mlx_destroy_image(r->mlx, r->door_frames[i].img);
		i += 1;
	}
	if (r->img)
		mlx_destroy_image(r->mlx, r->img);
	if (r->win)
		mlx_destroy_window(r->mlx, r->win);
	free_mat(map);
	free_mat(states);
}
