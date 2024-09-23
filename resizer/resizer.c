/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resizer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:17:51 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/16 18:28:11 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>

#include "error/error.h"
#include "error/codes.h"
#include "minilibx/mlx.h"
#include "game/t_texture.h"

static void	resized_texture_base(t_texture *src, t_texture *dst, int *sbuff,
				int *dbuff);

bool	resized_texture(void *mlx, t_texture *src, t_texture *dst, t_err *err)
{
	int	tmp;

	if ((src->h != dst->h || src->w != dst->w) && track(err, "resized_texture"))
	{
		dst->img = mlx_new_image(mlx, dst->w, dst->h);
		if (check_err(err, dst->img != NULL, MLX_ALLOC))
			resized_texture_base(src, dst,
				(int *)mlx_get_data_addr(src->img, &tmp, &tmp, &tmp),
				(int *)mlx_get_data_addr(dst->img, &tmp, &tmp, &tmp));
		untrack(err);
	}
	return (!err->error);
}

static void	resized_texture_base(t_texture *src, t_texture *dst, int *sbuff,
				int *dbuff)
{
	int	i;
	int	j;

	i = 0;
	while (i < dst->h)
	{
		j = 0;
		while (j < dst->w)
		{
			dbuff[i * dst->w + j] = sbuff[i * src->w * src->h / dst->h
				+ j * src->w / dst->w];
			j += 1;
		}
		i += 1;
	}
}
