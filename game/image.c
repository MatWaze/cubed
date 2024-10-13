/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:36:32 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/13 21:48:43 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

#include "minilibx/mlx.h"
#include "t_render.h"
#include "t_texture.h"
#include "error/error.h"
#include "error/codes.h"
#include "c3d_math/t_mat.h"
#include "raycast/t_rayhit.h"

#include <stdio.h>

bool	xpm_to_texture(const char *path, void *mlx, t_texture *texture,
			t_err *err)
{
	int	tmp;

	if (track(err, "xpm_to_texture") && check_err(err, access(path, R_OK) == 0,
			PARSING_FILE_NOT_OPEN))
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
	return (no_err(err));
}

const t_texture	*choose_texture(const t_render *r, const t_mat *states,
				const t_rayhit *hit)
{
	const t_texture	*t;

	if (hit->type == '1' || hit->type == 0)
		t = r->wall_sides + hit->side;
	else if (hit->type == 'D')
		t = r->door_frames + states->m[hit->idx.y][hit->idx.x];
	else
		t = NULL;
	return (t);
}
