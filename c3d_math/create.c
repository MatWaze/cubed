/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 06:48:28 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/21 03:00:03 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "t_mat.h"
#include "error/error.h"
#include "error/codes.h"

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
	return (!error->error);
}

void	free_mat(t_mat *mat)
{
	free(mat->m);
	mat->m = NULL;
	mat->w = 0;
	mat->h = 0;
}
