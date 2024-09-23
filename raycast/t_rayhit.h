/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_rayhit.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:36:26 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/17 15:41:58 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_RAYHIT_H
# define T_RAYHIT_H

typedef struct s_rayhit
{
	float	dist;
	int		v_cord;
	char	type;
	char	side;
}	t_rayhit;
#endif
