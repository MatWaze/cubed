/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_characters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:38:22 by mamazari          #+#    #+#             */
/*   Updated: 2024/09/09 18:26:03 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common/common.h"
#include "libft/libft.h"
#include <stdio.h>
#include <time.h>

int	is_xpm_file(char *filename)
{
	char	**strs;
	int		last;
	int		len;
	int		ans;

	strs = ft_split(filename, '/');
	last = split_count(strs) - 1;
	ans = 1;
	if (strs && strs[last])
	{
		len = ft_strlen(strs[last]);
		if (len > 4 && strs[last][len - 1] == 'm' && strs[last][len - 2] == 'p' && \
		strs[last][len - 3] == 'x' && strs[last][len - 4] == '.')
			ans = 0;
		free_arr(strs);
	}
	return (ans);
}

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

int	other_characters(char **map)
{
	int		i;
	int		j;
	char	*trim;

	i = 0;
	while (map[i])
	{
		trim = ft_strtrim(map[i], "\n ");
		if (trim == NULL)
			return (10);
		else
		{
			j = 0;
			while (trim[j])
			{
				if (is_set(trim[j], "01NSEW ") == 0 && free_return(trim))
					return (0);
				j++;
			}
		}
		free_return(trim);
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
	if (map)
	{
		while (map[i])
		{
			pos += char_count(map[i], "NSEW");
			i++;
		}
	}
	return (pos == 1);
}
