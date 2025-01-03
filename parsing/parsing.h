/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:29:34 by mamazari          #+#    #+#             */
/*   Updated: 2024/10/13 21:29:31 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "game/t_game.h"
# include "t_cub.h"
# include "error/t_err.h"

int		validation(char *filename, t_cub *cubed, t_err *err);
int		is_cub(char *filename);
void	get_orientation_pos(t_cub *cub);
int		set_imgs(t_game *game);

#endif
