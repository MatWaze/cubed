/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:42:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/11 19:35:48 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "c3d_math/c3d_math.h"
#include "game/t_game.h"
#include "t_raycast_internal.h"
#include "t_rayhit.h"

void		raycast_x(const t_game *game, t_raycast_internal *ri,
				t_rayhit *hit);
void		raycast_y(const t_game *game, t_raycast_internal *ri,
				t_rayhit *hit);
bool		check_hit_x(const t_game *game, t_raycast_internal *ri,
				t_rayhit *hit);
bool		check_hit_y(const t_game *game, t_raycast_internal *ri,
				t_rayhit *hit);
void		cross(t_raycast_internal *ri, const t_vec *ppos);
void		cross_int_x(t_raycast_internal *ri, const t_vec *ppos);
void		cross_int_y(t_raycast_internal *ri, const t_vec *ppos);
void		cross_int_xy(t_raycast_internal *ri, const t_vec *ppos);

static void	hit_x(const t_game *game, const t_vec *pos, t_raycast_internal *ri,
				t_rayhit *hit);
static void	hit_y(const t_game *game, const t_vec *pos, t_raycast_internal *ri,
				t_rayhit *hit);
static void	hit_xy(const t_game *game, const t_vec *pos, t_raycast_internal *ri,
				t_rayhit *hit);

void	raycast(const t_game *game, const t_vec *pos, const t_vec *dir,
			t_rayhit *hit)
{
	t_raycast_internal	ri;

	hit->type = '0';
	ri.i = 0;
	set_ivec(&ri.step, (dir->x > 0) * 2 - 1, (dir->y > 0) * 2 - 1);
	if (dir->x == 0.0)
		raycast_y(game, &ri, hit);
	else if (dir->y == 0.0)
		raycast_x(game, &ri, hit);
	else
	{
		set_vec(&ri.k, dir->x / dir->y, dir->y / dir->x);
		ri.cross = *pos;
		cross(&ri, pos);
		ri.sdy = square_distance(&ri.cy, pos);
		ri.sdx = square_distance(&ri.cx, pos);
		set_ivec(&hit->idx, (int)ri.cross.x,
			game->map->h - 1 - (int)(ri.cross.y));
		while (hit->type == '0')
			hit_xy(game, pos, &ri, hit);
	}
	if (hit->type == 'D')
		hit->side = game->states.m[hit->idx.y][hit->idx.x];
}

static void	hit_x(const t_game *game, const t_vec *pos, t_raycast_internal *ri,
				t_rayhit *hit)
{
	ri->cross = ri->cx;
	hit->idx.y = game->map->h - 1 - ((int)(ri->cross.y - (ri->step.y == -1)));
	check_hit_x(game, ri, hit);
	cross_int_y(ri, pos);
}

static void	hit_y(const t_game *game, const t_vec *pos, t_raycast_internal *ri,
				t_rayhit *hit)
{
	ri->cross = ri->cy;
	hit->idx.x = (int)(ri->cross.x - (ri->step.x == -1));
	check_hit_y(game, ri, hit);
	cross_int_x(ri, pos);
}

static void	hit_xy(const t_game *game, const t_vec *pos, t_raycast_internal *ri,
				t_rayhit *hit)
{
	t_ivec	idx;

	if (ri->i++ > (int)(WIN_WIDTH / CAMERA_HALF_FOV_TAN / 4))
		hit->type = 0;
	if (ri->sdy < ri->sdx)
		hit_y(game, pos, ri, hit);
	else if (ri->sdy > ri->sdx)
		hit_x(game, pos, ri, hit);
	else
	{
		set_ivec(&idx, hit->idx.x + ri->step.x, hit->idx.y - ri->step.y);
		if (game->map->m[idx.y][hit->idx.x] != '0')
			hit_y(game, pos, ri, hit);
		else if (game->map->m[hit->idx.y][idx.x] != '0')
			hit_x(game, pos, ri, hit);
		else
		{
			hit->idx = idx;
			ri->cross = ri->cy;
			check_hit_y(game, ri, hit);
			cross_int_xy(ri, pos);
		}
	}
	ri->sdy = square_distance(&ri->cy, pos);
	ri->sdx = square_distance(&ri->cx, pos);
}
