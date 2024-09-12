/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_texture.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:11:57 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/11 18:13:55 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_TEXTURE_H
# define T_TEXTURE_H

typedef struct s_texture
{
	int		w;
	int		h;
	void	*img;
}	t_texture;
#endif
