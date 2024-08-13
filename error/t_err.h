/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_err.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 06:53:40 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/12 07:43:39 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ERR_H
#define T_ERR_H
#include "libft/libft.h"
#include "t_trace.h"

typedef struct s_err
{
	int error;
	t_trace *trace;
} t_err;
#endif
