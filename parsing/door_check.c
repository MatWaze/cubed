/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:11:35 by mamazari          #+#    #+#             */
/*   Updated: 2024/10/08 19:30:30 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d_math/t_mat.h"
#include <sys/_types/_size_t.h>
#include "parsing/t_cub.h"

int	is_surrounded(t_mat *map, size_t i, size_t j);
int	is_set(char c, char *set);

void	get_orientation_pos(t_mat *mat, t_cub *cub)
{
	unsigned int	i;
	unsigned int	j;
	int				ans;

	i = -1;
	ans = 0;
	while (++i < mat->h)
	{
		j = -1;
		while (++j < mat->w)
		{
			if (is_set(mat->m[i][j], "NSEW"))
			{
				ans = 1;
				mat->m[i][j] = '0';
				cub->orientation = mat->m[i][j];
				cub->init_pos.x = j;
				cub->init_pos.y = i;
				break ;
			}
		}
		if (ans == 1)
			break ;
	}
}

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
