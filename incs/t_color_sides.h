/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_color_sides.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:07:11 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/08 17:15:39 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_COLOR_SIDES_H
# define T_COLOR_SIDES_H

# include "t_rgb.h"

typedef struct s_color_sides
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	t_rgb	floor_color;
	t_rgb	ceiling_color;
}			t_color_sides;
#endif