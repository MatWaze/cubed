/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:54:05 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/13 20:32:57 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include <stdint.h>

#include "c3d_math/c3d_math.h"
#include "c3d_math/t_ivec.h"
#include "game/config.h"
#include "minilibx/mlx.h"
#include "raycast/raycast.h"
#include "t_game.h"

const t_texture			*choose_texture(const t_render *r, const t_mat *states,
							const t_rayhit *hit);

static void				render_stripe(t_game *game, int x, const t_rayhit *hit);
static int				render_color_stripe(int *img_buff, int y,
							int color, int len);
static int				render_texture_stripe(int *buff, int y,
							const t_ivec *x_height, const t_texture *t);
static void				render_recursion(t_game *game, const t_vec *pos,
							const t_vec *dir, int x);

void	render(t_game *game)
{
	t_vec		step;
	t_vec		dir;
	int			x;

	vec_sub(&game->prot, &game->cam, &dir);
	vec_div(&game->cam, WIN_WIDTH / 2.0, &step);
	x = 0;
	while (x < WIN_WIDTH)
	{
		render_recursion(game, &game->ppos, &dir, x);
		vec_add(&dir, &step, &dir);
		x += 1;
	}
	mlx_put_image_to_window(game->r.mlx, game->r.win, game->r.img, 0, 0);
}

static void	render_recursion(t_game *game, const t_vec *pos, const t_vec *dir,
				int x)
{
	t_rayhit	hit;

	raycast(game, pos, dir, &hit);
	if (hit.type == 'D')
		render_recursion(game, &hit.pos, dir, x);
	render_stripe(game, x, &hit);
}

static void	render_stripe(t_game *game, int x, const t_rayhit *hit)
{
	t_ivec			x_height;
	const t_texture	*t;
	int				y;

	t = choose_texture(&game->r, &game->states, hit);
	if (t)
	{
		y = 0;
		if (hit->type == 0)
			x_height.y = 0;
		else if (isinf(hit->dist))
			x_height.y = INT32_MAX;
		else
			x_height.y = (int)(WIN_WIDTH / (2 * hit->dist
						* CAMERA_HALF_FOV_TAN));
		if (x_height.y < 0)
			x_height.y = INT32_MAX;
		y = render_color_stripe(game->r.img_buff + x, y, game->r.ceil_color,
				(WIN_HEIGHT - x_height.y) / 2);
		x_height.x = (int)(t->w * hit->v_cord);
		y = render_texture_stripe(game->r.img_buff + x, y, &x_height, t);
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
