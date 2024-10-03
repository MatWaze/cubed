/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:15:34 by mamazari          #+#    #+#             */
/*   Updated: 2024/09/12 11:36:18 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "error/error.h"
#include "common/common.h"
#include "c3d_math/c3d_math.h"
#include "t_cub.h"
#include "libft/libft.h"

int	other_characters(char **map);
int	player_pos(char **map);
int	map_closed_horizontally(char **map);
int	is_set(char c, char *set);
int	door_surrounded(t_mat *mat);

int	condition_for_texture(t_cub *args, char **s)
{
	int	ans;

	ans = 0;
	if ((ft_strcmp(s[0], "NO") == 0 && \
		args->col_sides.north_found == -1) || (ft_strcmp(s[0], "SO") == 0 && \
		args->col_sides.south_found == -1) || (ft_strcmp(s[0], "WE") == 0 && \
		args->col_sides.west_found == -1) || (ft_strcmp(s[0], "EA") == 0 && \
		args->col_sides.east_found == -1))
		ans = 1;
	return (ans);
}

int	is_closed_zero(t_mat *map, size_t i, size_t j)
{
	int		ans;

	ans = 1;
	if (map->m[i][j] == '0' || (is_set(map->m[i][j], "NSEWD")))
	{
		if ((i == 0 || i == map->h - 1 || j == 0 || j == map->w - 1) \
		|| (j > 0 && map->m[i][j - 1] == ' ') || \
		(j + 1 < ft_strlen(map->m[i]) && (map->m[i][j + 1] == ' ' || \
		map->m[i][j + 1] == '\0')) || (i > 0 && j < ft_strlen(map->m[i - 1]) \
		&& map->m[i - 1][j] == ' ') || (map->m[i + 1] && \
		j < ft_strlen(map->m[i + 1]) && map->m[i + 1][j] == ' '))
			ans = 0;
	}
	return (ans);
}

void	fill_matrix(t_mat *new_map, char **map)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	len;

	i = 0;
	while (i < new_map->h && map[i])
	{
		j = 0;
		len = (unsigned int)ft_strlen(map[i]);
		if (len > 0)
		{
			while (j < new_map->w)
			{
				if (j < len)
					new_map->m[i][j] = map[i][j];
				else
					new_map->m[i][j] = ' ';
				j++;
			}
		}
		i++;
	}
}

int	check_if_closed(t_mat *mat)
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
			ans = is_closed_zero(mat, i, j);
			if (ans == 0)
				break ;
			j++;
		}
		i++;
	}
	return (ans);
}

int	is_map_valid(t_cub *cubed)
{
	int				ans;
	t_mat			mat;
	static t_err	err = {0};
	int				other;

	mat.m = NULL;
	ans = 12;
	if (create_mat(&mat, get_map_width(cubed->map), \
	get_map_height(cubed->map), &err))
	{
		ans = 0;
		fill_matrix(&mat, cubed->map);
		other = other_characters(cubed->map);
		if (other != 10)
		{
			if (player_pos(cubed->map) == 0 || other == 0 \
			|| check_if_closed(&mat) == 0)
				ans = 1;
			else if (door_surrounded(&mat) == 4)
				ans = 4;
		}
		if (mat.m)
			free(mat.m);
	}
	return (ans);
}
