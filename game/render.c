/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:54:05 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/24 19:13:27 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "c3d_math/c3d_math.h"
#include "c3d_math/t_ivec.h"
#include "game/config.h"
#include "minilibx/mlx.h"
#include "raycast/raycast.h"
#include "t_game.h"

static void	render_stripe(t_game *game, t_ivec *idx, const t_rayhit *hit,
				bool draw_back);
static void	render_texture_stripe(int *buff, t_ivec *idx,
				const t_ivec *x_height, t_texture *t);

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
}

static void	render_stripe(t_game *game, t_ivec *idx, const t_rayhit *hit,
				bool draw_back)
{
	int		len;
	t_ivec	x_height;

	idx->y = 0;
	x_height.y = (int)(WIN_HEIGHT * (1.0f - hit->dist / CLIPPING_DISTANCE));
	len = (WIN_HEIGHT - x_height.y) / 2;
	if (draw_back)
	{
		while (idx->y < len)
			game->r.img_buff[WIN_WIDTH * idx->y++ + idx->x]
				= game->r.ceil_color;
	}
	else
		idx->y = len;
	len += x_height.y;
	x_height.x = (int)(game->r.textures[(int)hit->type][(int)hit->side].w
		* hit->v_cord);
	render_texture_stripe(game->r.img_buff, idx, &x_height,
		game->r.textures[(int)hit->type] + hit->side);
	if (draw_back)
	{
		while (idx->y < WIN_HEIGHT)
			game->r.img_buff[WIN_WIDTH * idx->y++ + idx->x]
				= game->r.floor_color;
	}
}

static void	render_texture_stripe(int *buff, t_ivec *idx,
				const t_ivec *x_height, t_texture *t)
{
	int	color;
	int	y;
	int	*tb;

	tb = (int *)mlx_get_data_addr(t->img, &color, &color, &color);
	y = 0;
	while (y < x_height->y)
	{
		color = tb[WIN_WIDTH * t->h * y++ / x_height->y
			+ x_height->x * t->w / WIN_WIDTH];
		if (color)
			buff[WIN_WIDTH * idx->y + idx->x] = color;
		idx->y += 1;
	}
}
