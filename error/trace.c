/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 07:32:47 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/15 00:44:40 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "t_err.h"
#include "codes.h"

bool	track(t_err *err, const char *name)
{
	t_list	*new;

	new = ft_lstnew((void *)name);
	if (new)
	{
		ft_lstadd_front((t_list **)&err->trace, new);
		err->trace = (t_trace *)new;
	}
	else
		err->error = C3D_TRACE_TRACK_ALL;
	return (new != NULL);
}

void	pop_trace(t_trace **trace)
{
	t_trace	*tmp;

	tmp = *trace;
	*trace = tmp->next;
	free(tmp);
}

void	untrack(t_err *err)
{
	if (!err->error)
		pop_trace(&err->trace);
}

bool	ok(t_err *err)
{
	return (!err->error);
}

bool	check_err(t_err *err, bool pred, int code)
{
	if (!pred)
	{
		if (code == C3D_ERRNO)
			err->error = errno;
		else
			err->error = code;
	}
	return (pred);
}
