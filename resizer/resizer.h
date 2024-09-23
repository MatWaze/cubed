/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resizer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:08:26 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/16 18:27:58 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "game/t_texture.h"

bool	resized_texture(void *mlx, t_texture *src, t_texture *dst);
#endif
