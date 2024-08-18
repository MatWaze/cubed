/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mat.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 04:39:33 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/14 04:39:59 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MAT_H
# define T_MAT_H

typedef struct s_mat
{
	unsigned int	w;
	unsigned int	h;
	char			**m;
}	t_mat;
#endif
