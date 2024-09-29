/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:54:05 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/29 20:16:03 by zanikin          ###   ########.fr       */
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

static void				render_stripe(t_game *game, t_ivec *idx,
							const t_rayhit *hit, bool draw_back);
static void				render_color_stripe(int *img_buff, t_ivec *idx,
							int color, int len);
static void				render_texture_stripe(int *buff, t_ivec *idx,
							const t_ivec *x_height, const t_texture *t);
static const t_texture	*choose_texture(char id, char side, const t_render *r);

void	render(t_game *game)
{
	t_rayhit	l1hit;
	t_rayhit	l2hit;
	t_vec		step;
	t_vec		dir;
	t_ivec		idx;

	vec_sub(&game->prot, &game->cam, &dir);
	vec_div(&game->cam, WIN_WIDTH / 2.0f, &step);
	idx.x = 0;
	while (idx.x < WIN_WIDTH)
	{
		raycast(game, &dir, &l1hit, true);
		if (l1hit.type == 'D')
		{
			raycast(game, &dir, &l2hit, false);
			render_stripe(game, &idx, &l2hit, false);
		}
		render_stripe(game, &idx, &l1hit, true);
		vec_add(&dir, &step, &dir);
		idx.x += 1;
	}
	mlx_put_image_to_window(game->r.mlx, game->r.win, game->r.img, 0, 0);
}

static void	render_stripe(t_game *game, t_ivec *idx, const t_rayhit *hit,
				bool draw_back)
{
	t_ivec			x_height;
	const t_texture	*texture;

	idx->y = 0;
	x_height.y = (int)(WIN_WIDTH * CAMERA_HALF_FOV_TAN / 2 / hit->dist);
	if (draw_back)
		render_color_stripe(game->r.img_buff, idx, game->r.ceil_color,
			(WIN_HEIGHT - x_height.y) / 2);
	texture = choose_texture(hit->type, hit->side, &game->r);
	if (texture)
	{
		x_height.x = (int)(texture->w * hit->v_cord);
		render_texture_stripe(game->r.img_buff, idx, &x_height, texture);
	}
	if (draw_back)
		render_color_stripe(game->r.img_buff, idx, game->r.floor_color,
			WIN_HEIGHT);
}

static void	render_color_stripe(int *img_buff, t_ivec *idx, int color, int len)
{
	while (idx->y < len)
		img_buff[WIN_WIDTH * idx->y++ + idx->x] = color;
}

static const t_texture	*choose_texture(char id, char side, const t_render *r)
{
	const t_texture	*texture;

	if (id == '1')
		texture = r->wall_sides + side;
	else if (id == 'D')
		texture = r->door_frames + side;
	else
		texture = NULL;
	return (texture);
}

static void	render_texture_stripe(int *buff, t_ivec *idx,
				const t_ivec *x_height, const t_texture *t)
{
	int	color;
	int	y;
	int	*tb;
	int	len;

	tb = (int *)mlx_get_data_addr(t->img, &color, &color, &color);
	if (idx->y + x_height->y > WIN_HEIGHT)
		len = WIN_HEIGHT;
	else
		len = idx->y + x_height->y;
	y = 0;
	while (idx->y < len)
	{
		color = tb[t->w * t->h * y++ / x_height->y
			+ x_height->x * t->w / WIN_HEIGHT];
		if (color)
			buff[WIN_WIDTH * idx->y + idx->x] = color;
		idx->y += 1;
	}
}
