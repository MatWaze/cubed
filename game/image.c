/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:36:32 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/09 15:40:38 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "minilibx/mlx.h"
#include "t_texture.h"
#include "error/error.h"
#include "error/codes.h"

bool	xpm_to_texture(const char *path, void *mlx, t_texture *texture,
			t_err *err)
{
	int	tmp;

	if (track(err, "xpm_to_texture"))
	{
		texture->img = mlx_xpm_file_to_image(mlx, (char *)path, &texture->w,
				&texture->h);
		if (check_err(err, texture->img != NULL, MLX_ALLOC))
		{
			texture->buff = (int *)mlx_get_data_addr(texture->img, &tmp, &tmp,
					&tmp);
			if (check_err(err, texture->buff != NULL, MLX_ADDR))
				untrack(err);
		}
	}
	return (ok(err));
}
