/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_game.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:33:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/15 18:20:22 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_GAME_H
# define T_GAME_H

# include "t_texture.h"
# include "config.h"
# include "c3d_math/t_vec.h"
# include "c3d_math/t_mat.h"
# include "error/t_err.h"

typedef struct s_cube
{
	t_texture	north_img;
	t_texture	south_img;
	t_texture	west_img;
	t_texture	east_img;
}	t_cube;

typedef struct s_render
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_buff;
	t_cube	textures[LAST_MAP_SYMBOL - FIRST_MAP_SYMBOL + 1];
}	t_render;

typedef struct s_game
{
	t_vec		ppos;
	t_vec		prot;
	t_vec		cam;
	t_mat		map;
	t_render	r;
	t_err		e;
}	t_game;
#endif
