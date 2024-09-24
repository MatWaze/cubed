/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 03:16:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/24 19:11:28 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "t_err.h"

bool	track(t_err *err, const char *name);
void	untrack(t_err *err);
bool	check_err(t_err *err, bool pred, int code);
void	print_trace(t_err *err);
#endif
