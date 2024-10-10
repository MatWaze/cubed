/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:57:36 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/09 20:52:56 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_raycast_internal.h"

void		cross_int_x(t_raycast_internal *ri, const t_vec *ppos);
void		cross_int_y(t_raycast_internal *ri, const t_vec *ppos);
void		cross_int_xy(t_raycast_internal *ri, const t_vec *ppos);
static void	cross_double_xy(t_raycast_internal *ri, const t_vec *ppos);

void	cross(t_raycast_internal *ri, const t_vec *ppos)
{
	if (ri->cross.x - (int)ri->cross.x == 0.0
		&& ri->cross.y - (int)ri->cross.y == 0.0)
		cross_int_xy(ri, ppos);
	else if (ri->cross.x - (int)ri->cross.x == 0.0)
		cross_int_x(ri, ppos);
	else if (ri->cross.y - (int)ri->cross.y == 0.0)
		cross_int_y(ri, ppos);
	else
		cross_double_xy(ri, ppos);
}

void	cross_int_x(t_raycast_internal *ri, const t_vec *ppos)
{
	ri->cy.x = (int)(ri->cross.x + ri->step.x);
	ri->cy.y = ri->k.y * (ri->cy.x - ppos->x) + ppos->y;
	ri->cx.y = (int)(ri->cross.y + (ri->step.y == 1));
	ri->cx.x = ri->k.x * (ri->cx.y - ppos->y) + ppos->x;
}

void	cross_int_y(t_raycast_internal *ri, const t_vec *ppos)
{
	ri->cy.x = (int)(ri->cross.x + (ri->step.x == 1));
	ri->cy.y = ri->k.y * (ri->cy.x - ppos->x) + ppos->y;
	ri->cx.y = (int)(ri->cross.y + ri->step.y);
	ri->cx.x = ri->k.x * (ri->cx.y - ppos->y) + ppos->x;
}

void	cross_int_xy(t_raycast_internal *ri, const t_vec *ppos)
{
	ri->cy.x = (int)(ri->cross.x + ri->step.x);
	ri->cy.y = ri->k.y * (ri->cy.x - ppos->x) + ppos->y;
	ri->cx.y = (int)(ri->cross.y + ri->step.y);
	ri->cx.x = ri->k.x * (ri->cx.y - ppos->y) + ppos->x;
}

static void	cross_double_xy(t_raycast_internal *ri, const t_vec *ppos)
{
	ri->cy.x = (int)(ri->cross.x + (ri->step.x == 1));
	ri->cy.y = ri->k.y * (ri->cy.x - ppos->x) + ppos->y;
	ri->cx.y = (int)(ri->cross.y + (ri->step.y == 1));
	ri->cx.x = ri->k.x * (ri->cx.y - ppos->y) + ppos->x;
}
