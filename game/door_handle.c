/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:13:56 by mamazari          #+#    #+#             */
/*   Updated: 2024/10/13 21:37:25 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game/t_game.h"
#include "raycast/raycast.h"

void	door_handle(t_game *game)
{
	t_rayhit	ray;

	raycast(game, &game->ppos, &game->prot, &ray);
	if (ray.type == 'D' && ray.dist <= 1.0f && \
	game->states.m[ray.idx.y][ray.idx.x] == 0)
	{
		game->timer = 0;
		game->states.m[ray.idx.y][ray.idx.x]++;
		game->door_hit = ray;
	}
	else if (ray.type == 'D' && ray.dist <= 1.0f && \
	game->states.m[ray.idx.y][ray.idx.x] == 9)
	{
		game->timer = 1600;
		ray.type = '0';
		game->door_hit = ray;
	}
}
