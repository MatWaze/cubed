/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:41 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/21 16:42:53 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "c3d_math/c3d_math.h"
#include "error/error.h"
#include "game/t_game.h"
#include "parsing/parsing.h"
#include "parsing/t_cub.h"

bool		xpm_to_texture(const char *path, void *mlx, t_texture *texture,
				t_err *err);

static bool	read_textures(t_game *game, t_cub *cub);

bool	set_level(t_game *game, t_cub *cub)
{
	if (track(&game->e, "test_level"))
	{
		game->map = &cub->mat;
		get_orientation_pos(cub);
		game->timer = 0;
		set_vec(&game->ppos, cub->init_pos.x + 0.5f,
			cub->mat.h - 1 - cub->init_pos.y + 0.5f);
		set_vec(&game->prot, (cub->orientation == 'E')
			+ (cub->orientation == 'W') * -1, (cub->orientation == 'N')
			+ (cub->orientation == 'S') * -1);
		set_vec(&game->cam, (cub->orientation == 'N') * CAMERA_HALF_FOV_TAN
			+ (cub->orientation == 'S') * -CAMERA_HALF_FOV_TAN,
			(cub->orientation == 'W') * CAMERA_HALF_FOV_TAN
			+ (cub->orientation == 'E') * -CAMERA_HALF_FOV_TAN);
		game->r.ceil_color = (cub->col_sides.ceiling_color.red << 16)
			+ (cub->col_sides.ceiling_color.green << 8)
			+ cub->col_sides.ceiling_color.blue;
		game->r.floor_color = (cub->col_sides.floor_color.red << 16)
			+ (cub->col_sides.floor_color.green << 8)
			+ cub->col_sides.floor_color.blue;
		if (read_textures(game, cub))
			untrack(&game->e);
	}
	return (!game->e.error);
}

static bool	read_textures(t_game *game, t_cub *cub)
{
	if (track(&game->e, "read_textures") && xpm_to_texture(cub->col_sides.north \
	, game->r.mlx, game->r.wall_sides + NORTH, &game->e) && \
	xpm_to_texture(cub->col_sides.west, game->r.mlx, game->r.wall_sides + WEST, \
	&game->e) && xpm_to_texture(cub->col_sides.south, game->r.mlx, \
	game->r.wall_sides + SOUTH, &game->e) && xpm_to_texture(cub->col_sides.east \
	, game->r.mlx, game->r.wall_sides + EAST, &game->e) && \
	xpm_to_texture("textures/sliding_door_1.xpm", game->r.mlx, \
	game->r.door_frames, &game->e) && xpm_to_texture(\
	"textures/sliding_door_2.xpm", game->r.mlx, game->r.door_frames + 1, \
	&game->e) && xpm_to_texture("textures/sliding_door_3.xpm", game->r.mlx, \
	game->r.door_frames + 2, &game->e) && xpm_to_texture(\
	"textures/sliding_door_4.xpm", game->r.mlx, game->r.door_frames + 3, \
	&game->e) && xpm_to_texture("textures/sliding_door_5.xpm", game->r.mlx, \
	game->r.door_frames + 4, &game->e) && xpm_to_texture(\
	"textures/sliding_door_6.xpm", game->r.mlx, game->r.door_frames + 5, \
	&game->e) && xpm_to_texture("textures/sliding_door_7.xpm", game->r.mlx, \
	game->r.door_frames + 6, &game->e) && xpm_to_texture(\
	"textures/sliding_door_8.xpm", game->r.mlx, game->r.door_frames + 7, \
	&game->e) && xpm_to_texture("textures/sliding_door_9.xpm", game->r.mlx, \
	game->r.door_frames + 8, &game->e) && xpm_to_texture(\
	"textures/sliding_door_10.xpm", game->r.mlx, game->r.door_frames + 9, \
	&game->e))
		untrack(&game->e);
	return (no_err(&game->e));
}
