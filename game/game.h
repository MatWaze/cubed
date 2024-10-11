/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:57:02 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/08 19:35:49 by mamazari         ###   ########.fr       */
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
