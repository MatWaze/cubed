/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:57:02 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/06 18:09:28 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "t_game.h"

void	render(t_game *game);
int		key_hook(int keycode, t_game *game);
int		mouse_look(t_game *game);
int		exit_game(t_game *game);
#endif
