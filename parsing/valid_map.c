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

#include <stdio.h>
#include <stdlib.h>

#include "common/common.h"
#include "libft/libft.h"
#include "incs/t_cub.h"

int	spaces_after_chars(char **map);
int	other_characters(char **map);
int	player_pos(char **map);
int	map_closed_horizontally(char **map);

int	map_closed_horizontally(char **map)
{
	int		i;
	int		j;
	int		ans;
	char	*trim;

	i = -1;
	while (map[++i])
	{
		// printf("|%s\n", map[i]);
		ans = 0;
		trim = ft_strtrim(map[i], " ");
		j = 0;
		if (trim[j] == '1')
			ans += 2;
		while (trim[j + 1])
			j++;
		if (trim[j] == '1')
			ans--;
		if (free_return(trim) && ans != 1)
			break ;
	}
	return (ans);
}

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

int	map_closed_vertically(char **map)
{
	int	j;
	int	i;
	int	width;
	int	height;
	char	**new_map;
	
	j = 0;
	width = get_map_width(map);
	printf("%d\n", width);
	height = get_map_height(map);
	printf("%d\n", height);
	new_map = (char **) malloc(sizeof(char *) * (height * width + 1));
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			if (i > (int) ft_strlen(map[j]))
				new_map[j][i] = 'X';
			else if (map[j][i])
				new_map[j][i] = map[j][i];
			printf("%c", new_map[j][i]);
			i++;
		}
		j++;
		printf("\n");
	}
	return (0);
}

int	is_map_valid(t_cub *cubed)
{
	int	ans;

	ans = 0;
	map_closed_vertically(cubed->map);
	if (player_pos(cubed->map) == 0 || other_characters(cubed->map) == 0 || \
	spaces_after_chars(cubed->map) == 0 || \
	map_closed_horizontally(cubed->map) != 1)
		ans = 1;
	return (ans);
}
