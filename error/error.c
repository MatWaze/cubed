/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 06:45:34 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/03 16:05:22 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "t_err.h"
#include "codes.h"
#include "libft/libft.h"

bool				track(t_err *err, const char *name);
bool				check_err(t_err *err, bool pred, int code);
void				pop_trace(t_trace **trace);

static void			do_nothing(void *content);
static void			print_error(t_err *err);
static const char	*other_error(t_err *err);

void	print_trace(t_err *err)
{
	static t_err	re_err = {0};

	if (err->error)
	{
		printf("Error\n");
		while (err->trace && !re_err.error)
		{
			track(&re_err, err->trace->name);
			pop_trace(&err->trace);
		}
		if (check_err(err, !re_err.error, C3D_TRACE_PRINT_ALL))
		{
			while (re_err.trace)
			{
				printf("%s:", re_err.trace->name);
				pop_trace(&re_err.trace);
			}
		}
		print_error(err);
	}
	ft_lstclear((t_list **)&err->trace, do_nothing);
	ft_lstclear((t_list **)&re_err.trace, do_nothing);
}

static void	do_nothing(void *content)
{
	(void)content;
	return ;
}

static void	print_error(t_err *err)
{
	const char	*str;

	if (err->error == C3D_ERRNO)
		str = strerror(err->error);
	else if (err->error == C3D_TRACE_TRACK_ALL)
		str = C3D_TRACE_TRACK_ALL_DESK;
	else if (err->error == C3D_TRACE_PRINT_ALL)
		str = C3D_TRACE_PRINT_ALL_DESK;
	else if (err->error == C3D_ALL)
		str = C3D_ALL_DESK;
	else if (err->error == C3D_MAIN_INV_PARAM)
		str = C3D_MAIN_INV_PARAM_DESK;
	else if (err->error == PARSING_MAP)
		str = PARSING_MAP_DESK;
	else if (err->error == PARSING_FILE_NOT_OPEN)
		str = PARSING_FILE_NOT_OPEN_DESK;
	else if (err->error == PARSING_TEXTURE_COLOR)
		str = PARSING_TEXTURE_COLOR_DESK;
	else
		str = other_error(err);
	if (!(err->error == C3D_TRACE_TRACK_ALL
			|| err->error == C3D_TRACE_PRINT_ALL))
		printf(" ");
	printf("%s\n", str);
}

static const char	*other_error(t_err *err)
{
	const char	*str;

	if (err->error == MLX_INIT)
		str = MLX_INIT_DESK;
	else if (err->error == MLX_ALLOC)
		str = MLX_ALLOC_DESK;
	else
		str = "Unknown error";
	return (str);
}
