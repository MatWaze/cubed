/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:42:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/06 17:41:10 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "c3d_math/c3d_math.h"
#include "game/t_game.h"
#include "t_raycast_internal.h"
#include "t_rayhit.h"

void		raycast_x(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors);
void		raycast_y(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors);
bool		check_hit_x(const t_game *game, t_raycast_internal *ri,
				t_rayhit *hit, bool hit_doors);
bool		check_hit_y(const t_game *game, t_raycast_internal *ri,
				t_rayhit *hit, bool hit_doors);
void		cross(t_raycast_internal *ri, const t_vec *ppos);
void		cross_int_x(t_raycast_internal *ri, const t_vec *ppos);
void		cross_int_y(t_raycast_internal *ri, const t_vec *ppos);
void		cross_int_xy(t_raycast_internal *ri, const t_vec *ppos);

static void	hit_x(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors);
static void	hit_y(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors);
static void	hit_xy(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors);

void	raycast(const t_game *game, const t_vec *dir, t_rayhit *hit,
			bool hit_doors)
{
	t_raycast_internal	ri;

	hit->type = '0';
	set_ivec(&ri.step, (dir->x > 0) * 2 - 1, (dir->y > 0) * 2 - 1);
	if (dir->x == 0.0f)
		raycast_y(game, &ri, hit, hit_doors);
	else if (dir->y == 0.0f)
		raycast_x(game, &ri, hit, hit_doors);
	else
	{
		set_vec(&ri.k, dir->x / dir->y, dir->y / dir->x);
		ri.cross = game->ppos;
		cross(&ri, &game->ppos);
		ri.sdy = square_distance(&ri.cy, &game->ppos);
		ri.sdx = square_distance(&ri.cx, &game->ppos);
		set_ivec(&hit->idx, (int)ri.cross.x,
			game->map.h - 1 - (int)(ri.cross.y));
		while (hit->type == '0')
			hit_xy(game, &ri, hit, hit_doors);
	}
	if (hit->type == 'D')
		hit->side = game->states.m[hit->idx.y][hit->idx.x];
}

static void	hit_x(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors)
{
	ri->cross = ri->cx;
	hit->idx.y = game->map.h - 1 - ((int)(ri->cross.y - (ri->step.y == -1)));
	check_hit_x(game, ri, hit, hit_doors);
	cross_int_y(ri, &game->ppos);
}

static void	hit_y(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors)
{
	ri->cross = ri->cy;
	hit->idx.x = (int)(ri->cross.x - (ri->step.x == -1));
	check_hit_y(game, ri, hit, hit_doors);
	cross_int_x(ri, &game->ppos);
}

static void	hit_xy(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors)
{
	t_ivec	idx;

	if (ri->sdy < ri->sdx)
		hit_y(game, ri, hit, hit_doors);
	else if (ri->sdy > ri->sdx)
		hit_x(game, ri, hit, hit_doors);
	else
	{
		set_ivec(&idx, hit->idx.x + ri->step.x, hit->idx.y - ri->step.y);
		if (game->map.m[idx.y][hit->idx.x] != '0')
			hit_y(game, ri, hit, hit_doors);
		else if (game->map.m[hit->idx.y][idx.x] != '0')
			hit_x(game, ri, hit, hit_doors);
		else
		{
			hit->idx = idx;
			ri->cross = ri->cy;
			check_hit_y(game, ri, hit, hit_doors);
			cross_int_xy(ri, &game->ppos);
		}
	}
	ri->sdy = square_distance(&ri->cy, &game->ppos);
	ri->sdx = square_distance(&ri->cx, &game->ppos);
}
