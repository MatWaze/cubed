/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:30:01 by mamazari          #+#    #+#             */
/*   Updated: 2024/10/21 17:02:06 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <string.h>
#include <Tk/X11/X.h>
#include "minilibx/mlx.h"
#include "error/error.h"
#include "error/codes.h"
#include "game/game.h"
#include "c3d_math/c3d_math.h"
#include "game/config.h"
#include <stdlib.h>
#include "parsing/parsing.h"
#include "common/common.h"
#include <stdio.h>
#include <unistd.h>

void		free_game(t_render *r, t_mat *map, t_mat *states);

static void	start_game(t_game *game, t_cub *cub, int tmp);
static void	free_minimap(t_render *r);

int	main2(int argc, char **argv)
{
	static t_cub	cub = {0};
	static t_game	game = {.e = {0}, .r = {0}, .states = {0}, .door_hit = {0}};

	game.r.mlx = mlx_init();
	if (track(&game.e, "main") && check_err(&game.e, argc == 2, \
	C3D_MAIN_INV_PARAM) && check_err(&game.e, access(argv[1], R_OK) == 0, \
	PARSING_FILE_NOT_OPEN) && check_err(&game.e, is_cub(argv[1]) == 1, \
	MAIN_INV_FILE_NAME))
	{
		if (validation(argv[1], &cub, &game.e) && set_imgs(&game) && set_level(\
		&game, &cub) && create_mat(&game.states, game.map->w, game.map->h, \
		&game.e) && check_err(&game.e, game.r.mlx != NULL, MLX_INIT) && \
		check_err(&game.e, argc == 2, C3D_MAIN_INV_PARAM))
			start_game(&game, &cub, 0);
	}
	print_trace(&game.e);
	free_game(&game.r, &cub.mat, &game.states);
	return (game.e.error);
}

int	main(int argc, char **argv)
{
	main2(argc, argv);
	system("leaks cub3D");
	return (0);
}

static void	start_game(t_game *game, t_cub *cub, int tmp)
{
	set_mat(&game->states, 0);
	game->r.win = mlx_new_window(game->r.mlx, WIN_WIDTH, WIN_HEIGHT,
			"cub3D");
	game->r.img = mlx_new_image(game->r.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (check_err(&game->e, game->r.win != NULL, MLX_ALLOC)
		&& check_err(&game->e, game->r.img != NULL, MLX_ALLOC))
	{
		game->r.img_buff = (int *)mlx_get_data_addr(game->r.img, &tmp,
				&tmp, &tmp);
		if (cub->map)
			free_arr(cub->map);
		if (free_return(cub->col_sides.north) && free_return(\
		cub->col_sides.south) && free_return(cub->col_sides.east) \
		&& free_return(cub->col_sides.west))
			;
		mlx_do_key_autorepeaton(game->r.mlx);
		mlx_hook(game->r.win, KeyPress, 0, key_hook, game);
		mlx_hook(game->r.win, DestroyNotify, 0, exit_game, game);
		mlx_loop_hook(game->r.mlx, loop_hook, game);
		mlx_mouse_move(game->r.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		mlx_mouse_hide();
		render(game);
		draw_minimap(game);
		mlx_loop(game->r.mlx);
	}
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
	free_minimap(r);
	if (r->img)
		mlx_destroy_image(r->mlx, r->img);
	if (r->win)
		mlx_destroy_window(r->mlx, r->win);
	free_mat(map);
	free_mat(states);
}

static void	free_minimap(t_render *r)
{
	if (r->img_bg.img)
		mlx_destroy_image(r->mlx, r->img_bg.img);
	if (r->img_block.img)
		mlx_destroy_image(r->mlx, r->img_block.img);
	if (r->img_door.img)
		mlx_destroy_image(r->mlx, r->img_door.img);
	if (r->img_open.img)
		mlx_destroy_image(r->mlx, r->img_open.img);
	if (r->img_pl.img)
		mlx_destroy_image(r->mlx, r->img_pl.img);
}
