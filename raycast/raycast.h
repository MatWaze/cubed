/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:31:47 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/11 19:31:43 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "game/t_game.h"
# include "c3d_math/t_vec.h"
# include "t_rayhit.h"

void	raycast(const t_game *game, const t_vec *pos, const t_vec *dir,
			t_rayhit *hit);
#endif
