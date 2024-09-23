/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 06:41:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/21 22:29:59 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C3D_MATH_H
# define C3D_MATH_H

#include "t_vec.h"
#include "t_ivec.h"
#include "t_segment.h"
# include "t_mat.h"
# include "error/t_err.h"

void	free_mat(t_mat *mat);
bool	create_mat(t_mat *mat, unsigned int w, unsigned int h, t_err *error);
float	square_distance(const t_vec *p1, const t_vec *p2);
void	set_vec(t_vec *v, float x, float y);
void	set_ivec(t_ivec *v, int x, int y);
#endif
