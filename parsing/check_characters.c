/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_characters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:38:22 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/13 14:02:44 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "common/common.h"
#include "incs/t_cub.h"
#include "libft/libft.h"

int	is_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	char_count(char *line, char *set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (is_set(line[i], set) == 1)
			count++;
		i++;
	}
	return (count);
}

int	spaces_after_chars(char **map)
{
	int		i;
	size_t	j;
	int		ans;

	i = -1;
	ans = 1;
	while (map[++i])
	{
		j = 0;
		while (j < ft_strlen(map[i]))
		{
			if (map[i][j] == ' ')
			{
				if ((j > 0 && !is_set(map[i][j - 1], "1 ")) \
				|| (j + 1 < ft_strlen(map[i]) && !is_set(map[i][j + 1], "1 ")) \
				|| (i > 0 && j < ft_strlen(map[i - 1]) && !is_set(map[i - 1][j] \
				, "1 ")) || (map[i + 1] && j < ft_strlen(map[i + 1]) && \
				!is_set(map[i + 1][j], "1 ")))
					ans = 0;
			}
			j++;
		}
	}
	return (ans);
}

int	other_characters(char **map)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 0;
	while (map[i])
	{
		trimmed = ft_strtrim(map[i], "\n ");
		if (ft_strlen(trimmed) == 0)
			return (0);
		else
		{
			j = 0;
			while (trimmed[j])
			{
				if (is_set(trimmed[j], "01NSEW ") == 0)
					return (0);
				j++;
			}
		}
		free_return(trimmed);
		i++;
	}
	return (1);
}

int	player_pos(char **map)
{
	int	pos;
	int	i;

	pos = 0;
	i = 0;
	while (map[i])
	{
		pos += char_count(map[i], "NSEW");
		i++;
	}
	return (pos == 1);
}
