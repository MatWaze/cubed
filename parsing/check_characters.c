/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_characters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:38:22 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/16 16:30:33 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common/common.h"
#include "libft/libft.h"

int	is_xpm_file(char *filename)
{
	int	len;
	int	ans;

	len = ft_strlen(filename);
	ans = 1;
	if (len > 4 && filename[len - 1] == 'm' && filename[len - 2] == 'p' && \
	filename[len - 3] == 'x' && filename[len - 4] == '.')
		ans = 0;
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
	char	*trimmed;

	i = 0;
	while (map[i])
	{
		trimmed = ft_strtrim(map[i], "\n ");
		if (*trimmed == '\0' && free_return(trimmed))
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
