/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:31:47 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/16 20:46:28 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include <stdbool.h>

# include "game/t_game.h"
# include "c3d_math/t_vec.h"
# include "t_rayhit.h"

void	raycast(const t_game *game, const t_vec *dir, t_rayhit *hit,
			bool hit_doors);
#endif
