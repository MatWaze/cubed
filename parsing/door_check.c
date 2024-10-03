/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:11:35 by mamazari          #+#    #+#             */
/*   Updated: 2024/09/16 19:11:36 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d_math/t_mat.h"
#include <stdlib.h>

int	is_surrounded(t_mat *map, size_t i, size_t j);

int	is_surrounded(t_mat *map, size_t i, size_t j)
{
	int	ans;

	ans = 1;
	if (map->m[i][j] == 'D' && !((map->m[i][j + 1] == '1' && \
	map->m[i][j - 1] == '1') || (map->m[i + 1][j] == '1' && \
	map->m[i - 1][j] == '1')))
		ans = 4;
	return (ans);
}

int	door_surrounded(t_mat *mat)
{
	size_t	i;
	size_t	j;
	int		ans;

	i = 0;
	ans = 1;
	while (ans == 1 && i < mat->h)
	{
		j = 0;
		while (j < mat->w)
		{
			ans = is_surrounded(mat, i, j);
			if (ans == 4)
				break ;
			j++;
		}
		i++;
	}
	return (ans);
}
