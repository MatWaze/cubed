/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distances.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:07:22 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/09 20:00:10 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "t_vec.h"

double	square_distance(const t_vec *p1, const t_vec *p2)
{
	double	x;
	double	y;

	x = p1->x - p2->x;
	y = p1->y - p2->y;
	return (x * x + y * y);
}

double	distance(const t_vec *p1, const t_vec *p2)
{
	return (sqrtf(square_distance(p1, p2)));
}
