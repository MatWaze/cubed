/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_trace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 07:40:54 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/12 07:42:45 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_TRACE_H
# define T_TRACE_H

typedef struct s_trace
{
	const char		*name;
	struct s_trace	*next;
}	t_trace;
#endif
