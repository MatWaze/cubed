/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cub.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:07:30 by mamazari          #+#    #+#             */
/*   Updated: 2024/10/04 16:23:36 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CUB_H
# define T_CUB_H

# include "c3d_math/t_mat.h"
# include "common/t_color_sides.h"

typedef struct s_cub
{
	t_color_sides	col_sides;
	int				fd;
	char			*name;
	char			**map;
	t_mat			mat;
}			t_cub;
#endif