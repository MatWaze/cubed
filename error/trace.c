/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 07:32:47 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/12 08:07:41 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "t_err.h"
#include "codes.h"

bool	track(t_err *err, const char *name)
{
	t_list	*new;

	new = ft_lstnew((void *)name);
	if (new)
	{
		ft_lstadd_front((t_list **)&err->trace, new);
		err->trace = new;
	}
	else
		err->error = C3D_TRACE_ALL;
	return (new != NULL);
}

void	untrack(t_err *err)
{
	t_trace	*tmp;

	tmp = err->trace;
	err->trace = tmp->next;
	free(tmp);
}
