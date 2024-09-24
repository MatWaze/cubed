/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:10:33 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/23 18:07:29 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec.h"

void	set_vec(t_vec *v, float x, float y);

void	vec_add(const t_vec *v1, const t_vec *v2, t_vec *rv)
{
	set_vec(rv, v1->x + v2->x, v1->y + v2->y);
}

void	vec_sub(const t_vec *v1, const t_vec *v2, t_vec *rv)
{
	set_vec(rv, v1->x - v2->x, v1->y - v2->y);
}

void	vec_mul(const t_vec *v, float a, t_vec *rv)
{
	set_vec(rv, v->x * a, v->y * a);
}

void	vec_div(const t_vec *v, float a, t_vec *rv)
{
	set_vec(rv, v->x / a, v->y / a);
}
