/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distances.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:07:22 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/03 16:06:24 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "t_vec.h"

float	square_distance(const t_vec *p1, const t_vec *p2)
{
	float	x;
	float	y;

	x = p1->x - p2->x;
	y = p1->y - p2->y;
	return (x * x + y * y);
}

float	distance(const t_vec *p1, const t_vec *p2)
{
	return (sqrtf(square_distance(p1, p2)));
}
