/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:27:40 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/09 20:00:11 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec.h"
#include "t_ivec.h"

void	set_vec(t_vec *v, double x, double y)
{
	v->x = x;
	v->y = y;
}

void	set_ivec(t_ivec *v, int x, int y)
{
	v->x = x;
	v->y = y;
}
