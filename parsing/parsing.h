/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:29:34 by mamazari          #+#    #+#             */
/*   Updated: 2024/10/10 16:58:39 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "game/t_game.h"
# include "t_cub.h"
# include "error/t_err.h"

int		validation(char *filename, t_cub *cubed, t_err *err);
int		is_cub(char *filename);
void	draw_minimap(t_game *game);
void	get_orientation_pos(t_mat *mat, t_cub *cub);
int		set_imgs(t_game *game);

#endif