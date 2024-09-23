/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:42:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/23 11:10:26 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "c3d_math/c3d_math.h"
#include "game/t_game.h"
#include "t_raycast_internal.h"
#include "t_rayhit.h"

static void	cross(t_raycast_internal *ri, const t_vec *ppos);
static void	raycast_x(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
			bool hit_doors);
static void	raycast_y(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
			bool hit_doors);

static void	hit_check(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors);

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
		set_ivec(&ri.step, (dir->x > 0) * 2 - 1, (dir->y > 0) * 2 - 1);
		while (!hit->type)
		{
			if (square_distance(&ri.cy, &game->ppos)
				< square_distance(&ri.cx, &game->ppos))
				ri.cross = ri.cy;
			else
				ri.cross = ri.cx;
			hit_check(game, &ri, hit, hit_doors);
			cross(&ri, &game->ppos);
		}
	}
}

static void	raycast_y(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
			bool hit_doors)
{
	set_vec(&ri->cross, game->ppos.x, (int)(game->ppos.y + ri->step.y));
	ri->step.y = 2 * (ri->step.y == 1) - 1;
	set_ivec(&ri->idx, (int)game->ppos.x,
		game->map.h - 1 - (int)(game->ppos.y + ri->step.y));
	hit->type = 0;
	while (!hit->type)
	{
		ri->symb = game->map.m[ri->idx.y][ri->idx.x];
		if (ri->symb && (hit_doors || ri->symb != 'D'))
		{
			hit->type = ri->symb;
			ri->cross.y = game->map.h - 1 - ri->idx.y + (ri->step.y == -1);
			hit->dist = square_distance(&game->ppos, &ri->cross);
			hit->side = (ri->step.x == 1) * 'S' + (ri->step.x == -1) * 'N';
			hit->v_cord = ri->cross.x;
		}
		ri->idx.y += ri->step.y;
	}
}

static void	raycast_x(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
			bool hit_doors)
{
	set_vec(&ri->cross, (int)(game->ppos.x + ri->step.x), game->ppos.y);
	ri->step.x = 2 * (ri->step.x == 1) - 1;
	set_ivec(&ri->idx, (int)(game->ppos.x + ri->step.x),
		game->map.h - 1 - (int)game->ppos.y);
	hit->type = 0;
	while (!hit->type)
	{
		ri->symb = game->map.m[ri->idx.y][ri->idx.x];
		if (ri->symb && (hit_doors || ri->symb != 'D'))
		{
			hit->type = ri->symb;
			ri->cross.x = ri->idx.x;
			hit->dist = square_distance(&game->ppos, &ri->cross);
			hit->side = (ri->step.x == 1) * 'W' + (ri->step.x == -1) * 'E';
			hit->v_cord = ri->cross.y;
		}
		ri->idx.x += ri->step.x;
	}
}

static void	cross(t_raycast_internal *ri, const t_vec *ppos)
{
	ri->cy.x = (int)(ri->cross.x + ri->step.x);
	ri->cy.y = ri->k.y * (ri->cy.x - ppos->x) + ppos->y;
	ri->cx.y = (int)(ri->cross.y + ri->step.y);
	ri->cx.x = ri->k.x * (ri->cx.y - ppos->y) + ppos->x;
}

static void	hit_check(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
				bool hit_doors)
{
	ri->idx.y = game->map.h - 1 - ((int)(ri->cross.y - 1 + (ri->step.y == 1)));
	ri->idx.x = (int)(ri->cross.x - 1 + (ri->step.x == 1));
	ri->symb = game->map.m[ri->idx.y][ri->idx.x];
	if (ri->symb && (hit_doors || ri->symb != 'D'))
	{
		hit->type = ri->symb;
		hit->dist = square_distance(&ri->cross, &game->ppos);
		if (ri->cross.x - (int)ri->cross.x == 0.0f)
		{
			hit->side = (ri->step.x == 1) * 'W' + (ri->step.x == -1) * 'E';
			if (ri->step.x == 1)
				hit->v_cord = 1.0f - ri->cross.y - (int)ri->cross.y;
			else
				hit->v_cord = ri->cross.y - (int)ri->cross.y;
		}
		else
		{
			hit->side = (ri->step.y == 1) * 'S' + (ri->step.y == -1) * 'N';
			if (ri->step.y == 1)
				hit->v_cord = ri->cross.x - (int)ri->cross.x;
			else
				hit->v_cord = 1.0f - ri->cross.x - (int)ri->cross.x;
		}
	}
}
