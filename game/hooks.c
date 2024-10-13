/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:23:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/13 20:49:06 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <Carbon/Carbon.h>
#include <math.h>
#include <unistd.h>

#include "game/game.h"
#include "raycast/t_rayhit.h"
#include "t_game.h"
#include "c3d_math/t_vec.h"
#include "error/error.h"
#include "minilibx/mlx.h"
#include "config.h"

void		free_game(t_render *r, t_mat *map, t_mat *states);
int			exit_game(t_game *game);
void		rotate(t_game *game, double cos_v, double sin_v);
void		move(t_game *game, double mdx, double mdy);

static void	switch_pointer(t_game *game);
void		door_handle(t_game *game);
int			mouse_look(t_game *game);

int	loop_hook(t_game *game)
{
	if (game->door_hit.type == 'D' && \
	game->states.m[game->door_hit.idx.y][game->door_hit.idx.x] != 9 && \
	game->states.m[game->door_hit.idx.y][game->door_hit.idx.x] != 0)
	{
		game->timer++;
		if (game->timer % 200 == 0)
		{
			game->states.m[game->door_hit.idx.y][game->door_hit.idx.x]++;
			render(game);
			draw_minimap(game);
		}
	}
	else if (game->door_hit.type == '0' && \
	game->states.m[game->door_hit.idx.y][game->door_hit.idx.x] != 0)
	{
		game->timer--;
		if (game->timer % 200 == 0)
		{
			game->states.m[game->door_hit.idx.y][game->door_hit.idx.x]--;
			render(game);
			draw_minimap(game);
		}
	}
	mouse_look(game);
	return (0);
}

int	mouse_look(t_game *game)
{
	int	x;
	int	y;

	if (!game->p_on)
	{
		mlx_mouse_get_pos(game->r.win, &x, &y);
		x -= WIN_WIDTH / 2;
		if (x)
		{
			rotate(game, cos(x * MOUSE_SENSIVITY), -sin(x * MOUSE_SENSIVITY));
			mlx_mouse_move(game->r.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		}
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
	else if (keycode == kVK_ANSI_P)
		switch_pointer(game);
	else if (keycode == kVK_ANSI_E)
		door_handle(game);
	return (0);
}

static void	switch_pointer(t_game *game)
{
	if (game->p_on)
	{
		mlx_mouse_move(game->r.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		mlx_mouse_hide();
		game->p_on = false;
	}
	else
	{
		mlx_mouse_show();
		game->p_on = true;
	}
}

int	exit_game(t_game *game)
{
	free_game(&game->r, game->map, &game->states);
	print_trace(&game->e);
	exit(game->e.error);
}
