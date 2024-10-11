/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cub.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:07:30 by mamazari          #+#    #+#             */
/*   Updated: 2024/10/10 16:14:05 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CUB_H
# define T_CUB_H

# include "c3d_math/t_ivec.h"
# include "c3d_math/t_mat.h"
# include "common/t_color_sides.h"

typedef struct s_cub
{
	t_color_sides	col_sides;
	int				fd;
	char			*name;
	char			door[5];
	char			orientation;
	char			**map;
	t_ivec			init_pos;
	t_mat			mat;
}			t_cub;
#endif