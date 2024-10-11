/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 06:41:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/10 19:51:47 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C3D_MATH_H
# define C3D_MATH_H

# include "t_vec.h"
# include "t_ivec.h"
# include "t_segment.h"
# include "t_mat.h"
# include "error/t_err.h"

void	free_mat(t_mat *mat);
bool	create_mat(t_mat *mat, unsigned int w, unsigned int h, t_err *error);
double	square_distance(const t_vec *p1, const t_vec *p2);
double	distance(const t_vec *p1, const t_vec *p2);
void	set_vec(t_vec *v, double x, double y);
void	set_ivec(t_ivec *v, int x, int y);
void	set_mat(t_mat *mat, char c);
void	vec_add(const t_vec *v1, const t_vec *v2, t_vec *rv);
void	vec_sub(const t_vec *v1, const t_vec *v2, t_vec *rv);
void	vec_mul(const t_vec *v, double a, t_vec *rv);
void	vec_div(const t_vec *v, double a, t_vec *rv);
#endif
