/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_game.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:33:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/23 19:17:25 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_GAME_H
# define T_GAME_H

# include "t_texture.h"
# include "config.h"
# include "c3d_math/t_vec.h"
# include "c3d_math/t_mat.h"
# include "error/t_err.h"

typedef struct s_render
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*img_buff;
	t_texture	textures[LAST_MAP_SYMBOL - FIRST_MAP_SYMBOL + 1][4];
	t_texture	door_frames[DOOR_FRAMES_COUNT];
	int			ceil_color;
	int			floor_color;
}	t_render;

typedef struct s_game
{
	t_vec		ppos;
	t_vec		prot;
	t_vec		cam;
	t_mat		map;
	t_mat		states;
	t_render	r;
	t_err		e;
}	t_game;
#endif
