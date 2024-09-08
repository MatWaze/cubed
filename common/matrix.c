/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:45:48 by mamazari          #+#    #+#             */
/*   Updated: 2024/09/08 21:35:10 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	get_map_width(char **map)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	max = 0;
	if (map)
	{
		while (map[i])
		{
			len = ft_strlen(map[i]);
			if (len > max)
				max = len;
			i++;
		}
	}
	return (max);
}

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
			i++;
	}
	return (i);
}
