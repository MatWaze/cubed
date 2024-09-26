/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:42:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/26 19:54:29 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "c3d_math/c3d_math.h"
#include "game/config.h"
#include "game/t_game.h"
#include "t_raycast_internal.h"
#include "t_rayhit.h"

void		raycast_x(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors);
void		raycast_y(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors);
bool	check_hit_y(const t_vec *ppos, t_raycast_internal *ri, t_rayhit *hit,
			bool hit_doors);
bool	check_hit_x(const t_vec *ppos, t_raycast_internal *ri, t_rayhit *hit,
			bool hit_doors);

static void	cross(t_raycast_internal *ri, const t_vec *ppos);
static void	hit_x(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors);
static void	hit_y(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors);
static void	hit_xy(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors);
static void	init_idx(const t_game *game, t_raycast_internal *ri,
				t_rayhit *hit);

void	raycast(const t_game *game, const t_vec *dir, t_rayhit *hit,
			bool hit_doors)
{
	t_raycast_internal	ri;

	hit->type = 0;
	set_ivec(&ri.step, dir->x > 0.0f, dir->y > 0.0f);
	if (dir->x == 0.0f)
		raycast_y(game, &ri, hit, hit_doors);
	else if (dir->y == 0.0f)
		raycast_x(game, &ri, hit, hit_doors);
	else
	{
		set_vec(&ri.k, dir->x / dir->y, dir->y / dir->x);
		ri.cross = game->ppos;
		cross(&ri, &game->ppos);
		init_idx(game, &ri, hit);
		set_ivec(&ri.step, (dir->x > 0) * 2 - 1, (dir->y > 0) * 2 - 1);
		while (!hit->type)
		{
			hit_xy(game, &ri, hit, hit_doors);
			cross(&ri, &game->ppos);
			ri.sdy = square_distance(&ri.cy, &game->ppos);
			ri.sdx = square_distance(&ri.cx, &game->ppos);
		}
	}
}

static void	cross(t_raycast_internal *ri, const t_vec *ppos)
{
	ri->cy.x = (int)(ri->cross.x + ri->step.x);
	ri->cy.y = ri->k.y * (ri->cy.x - ppos->x) + ppos->y;
	ri->cx.y = (int)(ri->cross.y + ri->step.y);
	ri->cx.x = ri->k.x * (ri->cx.y - ppos->y) + ppos->x;
}

static void	init_idx(const t_game *game, t_raycast_internal *ri,
				t_rayhit *hit)
{
	ri->sdy = square_distance(&ri->cy, &game->ppos);
	ri->sdx = square_distance(&ri->cx, &game->ppos);
	if (ri->sdy < ri->sdy)
		hit->idx.y = game->map.h - 1 - (int)(ri->cross.y);
	else
		hit->idx.x = (int)ri->cross.x;
}

static void	hit_x(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors)
{
	ri->cross = ri->cx;
	hit->idx.y = game->map.h - 1 - ((int)(ri->cross.y - (ri->step.y == -1)));
	ri->symb = game->map.m[hit->idx.y][hit->idx.x];
	check_hit_x(&game->ppos, ri, hit, hit_doors);
}

static void	hit_y(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors)
{
	ri->cross = ri->cy;
	hit->idx.x = (int)(ri->cross.x - (ri->step.x == -1));
	ri->symb = game->map.m[hit->idx.y][hit->idx.x];
	check_hit_y(&game->ppos, ri, hit, hit_doors);
}

static void	hit_xy(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors)
{
	t_ivec	idx;

	set_ivec(&idx, (int)(ri->cross.x - (ri->step.x == -1)),
		game->map.h - 1 - ((int)(ri->cross.y - (ri->step.y == -1))));
	if (ri->sdy < ri->sdx)
		hit_y(game, ri, hit, hit_doors);
	else if (ri->sdy > ri->sdx)
		hit_x(game, ri, hit, hit_doors);
	else if (game->map.m[idx.y][hit->idx.x] != '0')
		hit_y(game, ri, hit, hit_doors);
	else if (game->map.m[hit->idx.y][idx.x] != '0')
		hit_x(game, ri, hit, hit_doors);
	else
	{
		hit->idx.x = idx.x;
		hit_y(game, ri, hit, hit_doors);
	}
}
