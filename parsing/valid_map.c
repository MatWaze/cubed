/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:15:34 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/13 18:48:56 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "common/common.h"
#include "libft/libft.h"
#include "incs/t_cub.h"

int	spaces_after_chars(char **map);
int	other_characters(char **map);
int	player_pos(char **map);
int	map_closed_horizontally(char **map);
int	is_set(char c, char *set);

// int	map_closed_horizontally(char **map)
// {
// 	int		i;
// 	int		j;
// 	int		ans;
// 	char	*trim;

// 	i = -1;
// 	while (map[++i])
// 	{
// 		ans = 0;
// 		trim = ft_strtrim(map[i], " ");
// 		j = 0;
// 		if (trim[j] == '1')
// 			ans += 2;
// 		while ((j + 1) < (int) ft_strlen(trim) && \
// 		trim[j + 1])
// 			j++;
// 		if (trim[j] == '1')
// 			ans--;
// 		if (free_return(trim) && ans != 1)
// 			break ;
// 	}
// 	return (ans);
// }

int	get_map_width(char **map)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	max = -100;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	is_closed_zero(char **map, size_t i, size_t j)
{
	int	ans;

	ans = 1;
	if (map[i][j] == '0' || (is_set(map[i][j], "NSEW")))
	{
		if ((j > 0 && !is_set(map[i][j - 1], "10NSEW")) \
		|| (j + 1 < ft_strlen(map[i]) && !is_set(map[i][j + 1], "10NSEW")) \
		|| (i > 0 && j < ft_strlen(map[i - 1]) && !is_set(map[i - 1][j] \
		, "10NSEW")) || (map[i + 1] && j < ft_strlen(map[i + 1]) && \
		!is_set(map[i + 1][j], "10NSEW")))
			ans = 0;
	}
	return (ans);
}

int	check_if_closed(char **new_map)
{
	size_t	i;
	size_t	j;
	int		ans;
	char	*first_line;
	char	*last_line;

	i = 0;
	ans = 1;
	first_line = new_map[0];
	last_line = new_map[get_map_height(new_map) - 1];
	if (ft_strchr(first_line, '0') || ft_strchr(last_line, '0'))
		ans = 0;
	else
	{
		while (ans == 1 && new_map[i])
		{
			j = 0;
			while (new_map[i][j])
			{
				ans = is_closed_zero(new_map, i, j);
				if (ans == 0)
					break ;
				j++;
			}
			i++;
		}
	}
	return (ans);
}

// int	map_closed_vertically(char **map)
// {

// }

int	is_map_valid(t_cub *cubed)
{
	int	ans;

	ans = 0;
	if (player_pos(cubed->map) == 0 || other_characters(cubed->map) == 0 || \
	check_if_closed(cubed->map) == 0)
		ans = 1;
	return (ans);
}
