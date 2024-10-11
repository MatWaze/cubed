/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:30:01 by mamazari          #+#    #+#             */
/*   Updated: 2024/10/11 17:18:48 by zanikin          ###   ########.fr       */
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

bool	set_level(t_game *game, t_cub *cub);
void	free_game(t_render *r, t_mat *map, t_mat *states);

bool	set_level(t_game *game, t_cub *cub)
{
	float	k;
	float	l;

	if (track(&game->e, "test_level"))
	{
		game->map = &cub->mat;
		get_orientation_pos(game->map, cub);
		k = cub->init_pos.x + 0.5f;
		l = (cub->mat.h - 1 - cub->init_pos.y + 0.5f);
		game->ppos.x = k;
		game->ppos.y = l;
		game->prot.x = 0.0;
		game->prot.y = 1.0;
		game->cam.x = CAMERA_HALF_FOV_TAN;
		game->cam.y = 0.0;
		game->r.ceil_color = 0x6e5020;
		game->r.floor_color = 0xa68444;
		if (xpm_to_texture(cub->col_sides.north, game->r.mlx, game->r.wall_sides + NORTH, &game->e) &&
		xpm_to_texture(cub->col_sides.west, game->r.mlx, game->r.wall_sides + WEST, &game->e) &&
		xpm_to_texture(cub->col_sides.south, game->r.mlx, game->r.wall_sides + SOUTH, &game->e) &&
		xpm_to_texture(cub->col_sides.east, game->r.mlx, game->r.wall_sides + EAST, &game->e) &&
		xpm_to_texture("textures/sliding_door_1.xpm", game->r.mlx, game->r.door_frames, &game->e) &&
		xpm_to_texture("textures/sliding_door_2.xpm", game->r.mlx, game->r.door_frames + 1, &game->e) &&
		xpm_to_texture("textures/sliding_door_3.xpm", game->r.mlx, game->r.door_frames + 2, &game->e) &&
		xpm_to_texture("textures/sliding_door_4.xpm", game->r.mlx, game->r.door_frames + 3, &game->e) &&
		xpm_to_texture("textures/sliding_door_5.xpm", game->r.mlx, game->r.door_frames + 4, &game->e) &&
		xpm_to_texture("textures/sliding_door_6.xpm", game->r.mlx, game->r.door_frames + 5, &game->e) &&
		xpm_to_texture("textures/sliding_door_7.xpm", game->r.mlx, game->r.door_frames + 6, &game->e) &&
		xpm_to_texture("textures/sliding_door_8.xpm", game->r.mlx, game->r.door_frames + 7, &game->e) &&
		xpm_to_texture("textures/sliding_door_9.xpm", game->r.mlx, game->r.door_frames + 8, &game->e) &&
		xpm_to_texture("textures/sliding_door_10.xpm", game->r.mlx, game->r.door_frames + 9, &game->e))
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

int	main2(int argc, char **argv)
{
	static t_cub	cub = {0};
	static t_game	game = {.e = {0}, .r = {0}, .states = {0}};
	int				tmp;
	int				valid;

	valid = 0;
	(void)argv;
	game.r.mlx = mlx_init();
	if (track(&game.e, "main") && check_err(&game.e, argc == 2, \
	C3D_MAIN_INV_PARAM) && check_err(&game.e, access(argv[1], R_OK) == 0, \
	PARSING_FILE_NOT_OPEN) && check_err(&game.e, is_cub(argv[1]) == 1, \
	MAIN_INV_FILE_NAME))
	{
		tmp = set_imgs(&game);
		if (track(&game.e, "set_imgs") && check_err(&game.e, tmp == 1, PARSING_FILE_NOT_OPEN))
		{
			untrack(&game.e);
			valid = validation(argv[1], &cub, &game.e);
		}
		if (valid == 25 && set_level(&game, &cub) && create_mat(&game.states, game.map->w, game.map->h, &game.e) && check_err(&game.e, game.r.mlx != \
		NULL, MLX_INIT) && check_err(&game.e, argc == 2, C3D_MAIN_INV_PARAM))
		{
			set_mat(&game.states, 0);
			game.r.win = mlx_new_window(game.r.mlx, WIN_WIDTH, WIN_HEIGHT,
					"cub3D");
			game.r.img = mlx_new_image(game.r.mlx, WIN_WIDTH, WIN_HEIGHT);
			if (check_err(&game.e, game.r.win != NULL, MLX_ALLOC)
				&& check_err(&game.e, game.r.img != NULL, MLX_ALLOC))
			{
				game.r.img_buff = (int *)mlx_get_data_addr(game.r.img, &tmp,
						&tmp, &tmp);
				if (cub.map)
					free_arr(cub.map);
				if (free_return(cub.col_sides.north) && free_return(\
				cub.col_sides.south) && free_return(cub.col_sides.east) \
				&& free_return(cub.col_sides.west))
					;
				mlx_do_key_autorepeaton(game.r.mlx);
				mlx_hook(game.r.win, KeyPress, 0, key_hook, &game);
				mlx_hook(game.r.win, DestroyNotify, 0, exit_game, &game);
				mlx_loop_hook(game.r.mlx, mouse_look, &game);
				mlx_mouse_move(game.r.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
				mlx_mouse_hide();
				render(&game);
				draw_minimap(&game);
				mlx_loop(game.r.mlx);
			}
		}
	}
	untrack(&game.e);
	print_trace(&game.e);
	return (game.e.error);
}

int	main(int argc, char **argv)
{
	main2(argc, argv);
	// system("leaks cub3D");
	return (0);
}
