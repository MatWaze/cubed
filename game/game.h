/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:57:02 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/21 16:42:06 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "parsing/t_cub.h"
# include "t_game.h"

void	render(t_game *game);
int		key_hook(int keycode, t_game *game);
int		loop_hook(t_game *game);
int		exit_game(t_game *game);
bool	xpm_to_texture(const char *path, void *mlx, t_texture *texture,
			t_err *err);
void	draw_minimap(t_game *game);
bool	set_level(t_game *game, t_cub *cub);
#endif
