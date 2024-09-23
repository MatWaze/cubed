/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:10:33 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/18 13:12:28 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec.h"

float	square_distance(const t_vec *p1, const t_vec *p2)
{
	float	x;
	float	y;
	
	x = p1->x - p2->x;
	y = p1->y - p2->y;
	return (x * x + y * y);
}