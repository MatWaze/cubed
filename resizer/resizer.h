/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resizer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:08:26 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/11 18:15:44 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESIZER_H
# define RESIZER_H

# include "game/t_texture.h"

void	resized_text(t_texture *src, t_texture *dst, int w, int h);
#endif
