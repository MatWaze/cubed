/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_direct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:27:30 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/13 21:24:05 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game/t_game.h"
#include "t_raycast_internal.h"
#include "t_rayhit.h"
#include "c3d_math/c3d_math.h"
#include <stdbool.h>

bool	check_hit_x(const t_game *game, t_raycast_internal *ri, t_rayhit *hit);
bool	check_hit_y(const t_game *game, t_raycast_internal *ri, t_rayhit *hit);

void	raycast_y(const t_game *game, t_raycast_internal *ri, t_rayhit *hit)
{
	if (game->ppos.y - (int)game->ppos.y == 0.0)
		set_vec(&ri->cross, game->ppos.x, (int)(game->ppos.y + ri->step.y));
	else
		set_vec(&ri->cross, game->ppos.x,
			(int)(game->ppos.y + (ri->step.y == 1)));
	set_ivec(&hit->idx, (int)game->ppos.x,
		game->map->h - 1 - (int)(game->ppos.y + ri->step.y));
	while (hit->type == '0')
	{
		if (ri->i++ > (int)(WIN_WIDTH / CAMERA_HALF_FOV_TAN / 4))
			hit->type = 0;
		else
		{
			if (!check_hit_x(game, ri, hit))
				hit->idx.y -= ri->step.y;
		}
	}
	ri->cross.y = game->map->h - 1 - hit->idx.y + (ri->step.y == -1);
	hit->pos = ri->cross;
}

void	raycast_x(const t_game *game, t_raycast_internal *ri, t_rayhit *hit)
{
	if (game->ppos.x - (int)game->ppos.x == 0.0)
		set_vec(&ri->cross, (int)(game->ppos.x + ri->step.x), game->ppos.y);
	else
		set_vec(&ri->cross, (int)(game->ppos.x + (ri->step.x == 1)),
			game->ppos.y);
	set_ivec(&hit->idx, (int)(game->ppos.x + ri->step.x),
		game->map->h - 1 - (int)game->ppos.y);
	while (hit->type == '0')
	{
		if (ri->i++ > (int)(WIN_WIDTH / CAMERA_HALF_FOV_TAN / 4))
			hit->type = 0;
		else
		{
			if (!check_hit_y(game, ri, hit))
				hit->idx.x += ri->step.x;
		}
	}
	ri->cross.x = hit->idx.x - (ri->step.x == -1);
	hit->pos = ri->cross;
}

bool	check_hit_x(const t_game *game, t_raycast_internal *ri, t_rayhit *hit)
{
	bool	hitted;

	hitted = false;
	if (hit->idx.y > -1 && (unsigned int)hit->idx.y < game->map->h && hit->idx.x
		> -1 && (unsigned int)hit->idx.x < game->map->w)
	{
		ri->symb = game->map->m[hit->idx.y][hit->idx.x];
		if (ri->symb != '0')
		{
			hit->type = ri->symb;
			hit->dist = distance(&game->ppos, &ri->cross);
			hit->side = (ri->step.y == 1) * SOUTH + (ri->step.y == -1) * NORTH;
			if (ri->step.y == 1)
				hit->v_cord = ri->cross.x - (int)ri->cross.x;
			else
				hit->v_cord = 1.0 - ri->cross.x + (int)ri->cross.x;
			hitted = true;
		}
	}
	else
		hit->type = 0;
	return (hitted);
}

bool	check_hit_y(const t_game *game, t_raycast_internal *ri, t_rayhit *hit)
{
	bool	hitted;

	hitted = false;
	if (hit->idx.y > -1 && (unsigned int)hit->idx.y < game->map->h && hit->idx.x
		> -1 && (unsigned int)hit->idx.x < game->map->w)
	{
		ri->symb = game->map->m[hit->idx.y][hit->idx.x];
		if (ri->symb != '0')
		{
			hit->type = ri->symb;
			hit->dist = distance(&game->ppos, &ri->cross);
			hit->side = (ri->step.x == 1) * WEST + (ri->step.x == -1) * EAST;
			if (ri->step.x == 1)
				hit->v_cord = 1.0 - ri->cross.y + (int)ri->cross.y;
			else
				hit->v_cord = ri->cross.y - (int)ri->cross.y;
			hitted = true;
		}
	}
	else
		hit->type = 0;
	return (hitted);
}
