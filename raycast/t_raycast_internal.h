/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_raycast_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:11:49 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/26 18:33:07 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_RAYCAST_INTERNAL
# define T_RAYCAST_INTERNAL

#include "c3d_math/t_segment.h"
#include "c3d_math/t_ivec.h"

typedef struct s_raycast_internal
{
	t_ivec	step;
	char	symb;
	t_vec	cross;
	t_vec	cx;
	t_vec	cy;
	t_vec	k;
	float	sdx;
	float	sdy;
}	t_raycast_internal;
#endif
