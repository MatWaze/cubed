/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cub.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:07:30 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/10 18:57:59 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CUB_H
# define T_CUB_H

# include "common/t_color_sides.h"

typedef struct s_cub
{
	t_color_sides	col_sides;
	int				fd;
	char			*name;
	char			**map;
}			t_cub;
#endif