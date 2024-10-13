/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:04:21 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/13 19:59:32 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "t_game.h"
#include "raycast/raycast.h"
#include "c3d_math/c3d_math.h"

void		render(t_game *game);
void		draw_minimap(t_game *game);

void	rotate(t_game *game, double cos_v, double sin_v)
{
	double	x;

	x = game->prot.x;
	game->prot.x = cos_v * x - sin_v * game->prot.y;
	game->prot.y = sin_v * x + cos_v * game->prot.y;
	x = game->cam.x;
	game->cam.x = cos_v * x - sin_v * game->cam.y;
	game->cam.y = sin_v * x + cos_v * game->cam.y;
	render(game);
	draw_minimap(game);
}

void	move(t_game *game, double mdx, double mdy)
{
	t_rayhit	hit;
	t_vec		dist;
	t_vec		dir;

	set_vec(&dir, mdx, mdy);
	raycast(game, &game->ppos, &dir, &hit);
	set_vec(&dist, hit.pos.x - game->ppos.x, hit.pos.y - game->ppos.y);
	vec_mul(&dir, MOVEMENT_RESOLUTION, &dir);
	if (!(hit.type == 'D' && game->states.m[hit.idx.y][hit.idx.x] == 9))
	{
		if (fabs(dist.x) < fabs(dir.x))
			dir.x = 0;
		if (fabs(dist.y) < fabs(dir.y))
			dir.y = 0;
	}
	vec_add(&game->ppos, &dir, &game->ppos);
	render(game);
	draw_minimap(game);
}
