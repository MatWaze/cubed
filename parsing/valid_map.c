/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:15:34 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/13 14:11:50 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/t_cub.h"

int	spaces_after_chars(char **map);
int	other_characters(char **map);
int	player_pos(char **map);

int	is_map_valid(t_cub *cubed)
{
	int	ans;

	ans = 0;
	if (player_pos(cubed->map) == 0 || other_characters(cubed->map) == 0 || \
	spaces_after_chars(cubed->map) == 0)
		ans = 1;
	return (ans);
}