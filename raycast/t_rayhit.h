/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_rayhit.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:36:26 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/03 16:07:23 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_RAYHIT_H
# define T_RAYHIT_H

# include "c3d_math/t_ivec.h"

typedef struct s_rayhit
{
	t_ivec	idx;
	float	dist;
	float	v_cord;
	char	type;
	char	side;
}	t_rayhit;
#endif
