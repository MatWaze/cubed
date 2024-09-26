/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_direct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:27:30 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/26 19:29:32 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game/t_game.h"
#include "t_raycast_internal.h"
#include "t_rayhit.h"
#include "c3d_math/c3d_math.h"
#include <stdbool.h>

bool	check_hit_y(const t_vec *ppos, t_raycast_internal *ri, t_rayhit *hit,
			bool hit_doors);
bool	check_hit_x(const t_vec *ppos, t_raycast_internal *ri, t_rayhit *hit,
			bool hit_doors);

void	raycast_y(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
			bool hit_doors)
{
	set_vec(&ri->cross, game->ppos.x, (int)(game->ppos.y + ri->step.y));
	ri->step.y = 2 * (ri->step.y == 1) - 1;
	set_ivec(&hit->idx, (int)game->ppos.x,
		game->map.h - 1 - (int)(game->ppos.y + ri->step.y));
	hit->type = 0;
	while (!hit->type)
	{
		ri->symb = game->map.m[hit->idx.y][hit->idx.x];
		if (!check_hit_y(&game->ppos, ri, hit, hit_doors))
			hit->idx.y += ri->step.y;
	}
	ri->cross.y = game->map.h - 1 - hit->idx.y + (ri->step.y == -1);
}

void	raycast_x(const t_game *game, t_raycast_internal *ri, t_rayhit *hit,
			bool hit_doors)
{
	set_vec(&ri->cross, (int)(game->ppos.x + ri->step.x), game->ppos.y);
	ri->step.x = 2 * (ri->step.x == 1) - 1;
	set_ivec(&hit->idx, (int)(game->ppos.x + ri->step.x),
		game->map.h - 1 - (int)game->ppos.y);
	hit->type = 0;
	while (!hit->type)
	{
		ri->symb = game->map.m[hit->idx.y][hit->idx.x];
		if (!check_hit_x(&game->ppos, ri, hit, hit_doors))
			hit->idx.x += ri->step.x;
	}
	ri->cross.x = hit->idx.x - (ri->step.x == -1);
}

bool	check_hit_y(const t_vec *ppos, t_raycast_internal *ri, t_rayhit *hit,
			bool hit_doors)
{
	bool	hitted;

	if (ri->symb != '0' && (hit_doors || ri->symb != 'D'))
	{
		hit->type = ri->symb;
		hit->dist = distance(ppos, &ri->cross);
		hit->side = (ri->step.x == 1) * SOUTH + (ri->step.x == -1) * NORTH;
		if (ri->step.y == 1)
			hit->v_cord = ri->cross.x - (int)ri->cross.x;
		else
			hit->v_cord = 1.0f - ri->cross.x - (int)ri->cross.x;
		hitted = true;
	}
	else
		hitted = false;
	return (hitted);
}

bool	check_hit_x(const t_vec *ppos, t_raycast_internal *ri, t_rayhit *hit,
			bool hit_doors)
{
	bool	hitted;

	if (ri->symb != '0' && (hit_doors || ri->symb != 'D'))
	{
		hit->type = ri->symb;
		hit->dist = distance(ppos, &ri->cross);
		hit->side = (ri->step.x == 1) * WEST + (ri->step.x == -1) * EAST;
		if (ri->step.x == 1)
			hit->v_cord = 1.0f - ri->cross.y - (int)ri->cross.y;
		else
			hit->v_cord = ri->cross.y - (int)ri->cross.y;
		hitted = true;
	}
	else
		hitted = false;
	return (hitted);
}
