/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 06:48:28 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/10 16:44:05 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "t_mat.h"
#include "error/error.h"
#include "error/codes.h"
#include <stdio.h>

bool	create_mat(t_mat *mat, unsigned int w, unsigned int h, t_err *error)
{
	char	*row;

	if (track(error, "create_mat") && check_err(error, w && h, C3D_INV_PAR))
	{
		mat->m = (char **)malloc(sizeof(char) * w * h + sizeof(char *) * h);
		if (check_err(error, mat->m != NULL, C3D_ALL))
		{
			mat->w = w;
			mat->h = h;
			row = (char *)(mat->m + h) + (w * (h - 1));
			while (h)
			{
				mat->m[h-- - 1] = row;
				row -= w;
			}
		}
		untrack(error);
	}
	print_trace(error);
	return (!error->error);
}
