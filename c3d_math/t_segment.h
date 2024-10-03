/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_segment.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:17:41 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/03 16:06:51 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SEGMENT_H
# define T_SEGMENT_H

# include "t_vec.h"

typedef struct s_segment
{
	t_vec	start;
	t_vec	end;
}	t_segment;
#endif
