/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:23:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/11 17:12:43 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <Carbon/Carbon.h>
#include <math.h>

#include "t_game.h"
#include "c3d_math/t_vec.h"
#include "error/error.h"
#include "minilibx/mlx.h"
#include "config.h"

void		render(t_game *game);
void		free_game(t_render *r, t_mat *map, t_mat *states);
int			exit_game(t_game *game);
void		draw_minimap(t_game *game);

static void	rotate(t_game *game, double cos_v, double sin_v);
static void	move(t_game *game, double mdx, double mdy);

int	mouse_look(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->r.win, &x, &y);
	x -= WIN_WIDTH / 2;
	if (x)
	{
		rotate(game, cosf(x * MOUSE_SENSIVITY), -sin(x * MOUSE_SENSIVITY));
		mlx_mouse_move(game->r.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	}
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == kVK_Escape)
		exit_game(game);
	else if (keycode == kVK_LeftArrow)
		rotate(game, ROTATION_RESOLUTION_COS, ROTATION_RESOLUTION_SIN);
	else if (keycode == kVK_RightArrow)
		rotate(game, ROTATION_RESOLUTION_COS, -ROTATION_RESOLUTION_SIN);
	else if (keycode == kVK_ANSI_W)
		move(game, game->prot.x, game->prot.y);
	else if (keycode == kVK_ANSI_S)
		move(game, -game->prot.x, -game->prot.y);
	else if (keycode == kVK_ANSI_A)
		move(game, -game->prot.y, game->prot.x);
	else if (keycode == kVK_ANSI_D)
		move(game, game->prot.y, -game->prot.x);
	return (0);
}

static void	rotate(t_game *game, double cos_v, double sin_v)
{
	double	x;

	x = game->prot.x;
	game->prot.x = cos_v * x - sin_v * game->prot.y;
	game->prot.y = sin_v * x + cos_v * game->prot.y;
	x = game->cam.x;
	game->cam.x = cos_v * x - sin_v * game->cam.y;
	game->cam.y = sin_v * x + cos_v * game->cam.y;
	render(game);
	draw_minimap(game);
}

static void	move(t_game *game, double mdx, double mdy)
{
	game->ppos.x += mdx * MOVEMENT_RESOLUTION;
	game->ppos.y += mdy * MOVEMENT_RESOLUTION;
	render(game);
	draw_minimap(game);
}

int	exit_game(t_game *game)
{
	free_game(&game->r, game->map, &game->states);
	system("leaks cub3D");
	// untrack(&game->e);
	print_trace(&game->e);
	exit(game->e.error);
}
