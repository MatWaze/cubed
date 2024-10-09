/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:09:42 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/09 16:14:31 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_game.h"

void	render_background(t_game *game);
void	render_walls(t_game *game);

void	render(t_game *game)
{
	render_background(game);
	render_walls(game);
}
