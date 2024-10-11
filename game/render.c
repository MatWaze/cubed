/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:54:05 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/11 15:49:21 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "c3d_math/c3d_math.h"
#include "c3d_math/t_ivec.h"
#include "game/config.h"
#include "minilibx/mlx.h"
#include "raycast/raycast.h"
#include "t_game.h"

static void				render_stripe(t_game *game, int x, const t_rayhit *hit);
static int				render_color_stripe(int *img_buff, int y,
							int color, int len);
static int				render_texture_stripe(int *buff, int y,
							const t_ivec *x_height, const t_texture *t);
static const t_texture	*choose_texture(char id, char side, const t_render *r);

void	render(t_game *game)
{
	t_rayhit	l1hit;
	t_rayhit	l2hit;
	t_vec		step;
	t_vec		dir;
	int			x;

	vec_sub(&game->prot, &game->cam, &dir);
	vec_div(&game->cam, WIN_WIDTH / 2.0, &step);
	x = 0;
	while (x < WIN_WIDTH)
	{
		raycast(game, &dir, &l1hit, true);
		if (l1hit.type == 'D')
		{
			l1hit.side = game->states.m[l1hit.idx.y][l1hit.idx.x];
			raycast(game, &dir, &l2hit, false);
			render_stripe(game, x, &l2hit);
		}
		render_stripe(game, x, &l1hit);
		vec_add(&dir, &step, &dir);
		x += 1;
	}
	mlx_put_image_to_window(game->r.mlx, game->r.win, game->r.img, 0, 0);
}

static void	render_stripe(t_game *game, int x, const t_rayhit *hit)
{
	t_ivec			x_height;
	const t_texture	*texture;
	int				y;

	texture = choose_texture(hit->type, hit->side, &game->r);
	if (texture)
	{
		y = 0;
		if (hit->type == 0)
			x_height.y = 0;
		else
			x_height.y = (int)(WIN_WIDTH / (2 * hit->dist
						* CAMERA_HALF_FOV_TAN));
		y = render_color_stripe(game->r.img_buff + x, y, game->r.ceil_color,
				(WIN_HEIGHT - x_height.y) / 2);
		x_height.x = (int)(texture->w * hit->v_cord);
		y = render_texture_stripe(game->r.img_buff + x, y, &x_height, texture);
		y = render_color_stripe(game->r.img_buff + x, y,
				game->r.floor_color, WIN_HEIGHT);
	}
}

static int	render_color_stripe(int *img_buff, int y, int color, int len)
{
	while (y < len)
		img_buff[WIN_WIDTH * y++] = color;
	return (y);
}

static const t_texture	*choose_texture(char id, char side, const t_render *r)
{
	const t_texture	*texture;

	if (id == '1' || id == 0)
		texture = r->wall_sides + side;
	else if (id == 'D')
		texture = r->door_frames + side;
	else
		texture = NULL;
	return (texture);
}

static int	render_texture_stripe(int *buff, int gy,
				const t_ivec *x_height, const t_texture *t)
{
	int	color;
	int	y;
	int	len;

	if (gy + x_height->y > WIN_HEIGHT)
	{
		len = WIN_HEIGHT;
		y = (gy + x_height->y - WIN_HEIGHT) / 2;
	}
	else
	{
		len = gy + x_height->y;
		y = 0;
	}
	while (gy < len)
	{
		color = t->buff[t->h * y++ / x_height->y * t->w + x_height->x];
		if (color)
			buff[WIN_WIDTH * gy] = color;
		gy += 1;
	}
	return (gy);
}
