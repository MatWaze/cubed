/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 06:48:28 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/15 00:54:41 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "t_mat.h"
#include "error/error.h"
#include "error/codes.h"
#include "libft/libft.h"

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