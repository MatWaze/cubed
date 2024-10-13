/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_game.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:33:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/13 20:50:38 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_GAME_H
# define T_GAME_H

# include "raycast/t_rayhit.h"
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
	void		*img_block;
	void		*img_bg;
	void		*img_pl;
	void		*img_door;
	void		*img_open;
	int			*img_buff;
	t_texture	wall_sides[4];
	t_texture	door_frames[DOOR_FRAMES_COUNT];
	int			ceil_color;
	int			floor_color;
}	t_render;

typedef struct s_game
{
	bool		p_on;
	t_vec		ppos;
	t_vec		prot;
	t_vec		cam;
	long		timer;
	t_rayhit	door_hit;
	t_mat		*map;
	t_mat		states;
	t_render	r;
	t_err		e;
}	t_game;
#endif
