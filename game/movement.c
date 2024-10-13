/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:04:21 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/13 15:05:27 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_game.h"

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
	game->ppos.x += mdx * MOVEMENT_RESOLUTION;
	game->ppos.y += mdy * MOVEMENT_RESOLUTION;
	render(game);
	draw_minimap(game);
}
