/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c3d_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 06:41:15 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/21 03:00:11 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C3D_MATH_H
# define C3D_MATH_H

# include "t_mat.h"
# include "error/t_err.h"

void	free_mat(t_mat *mat);
bool	create_mat(t_mat *mat, unsigned int w, unsigned int h, t_err *error);
#endif
