/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:16:52 by mamazari          #+#    #+#             */
/*   Updated: 2024/09/09 18:56:57 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "libft/libft.h"
#include "common/common.h"
#include "t_cub.h"

int		is_valid_str(char *line, char **s, t_cub *args);
int		fr(char *line, char *trim, char **split);

void	any_null(t_cub *args, int *res, int *ans)
{
	if (args->col_sides.east_found == 0 && \
	args->col_sides.east == NULL)
	{
		*ans = 10;
		*res = 10;
	}
	else if (args->col_sides.west_found == 0 && \
	args->col_sides.west == NULL)
	{
		*ans = 10;
		*res = 10;
	}
	else if (args->col_sides.south_found == 0 && \
	args->col_sides.south == NULL)
	{
		*ans = 10;
		*res = 10;
	}
	else if (args->col_sides.north_found == 0 && \
	args->col_sides.north == NULL)
	{
		*ans = 10;
		*res = 10;
	}
}

int	fr(char *line, char *trim, char **split)
{
	if (line)
	{
		free(line);
	}
	if (trim)
	{
		free(trim);
	}
	if (split)
	{
		free_arr(split);
	}
	return (0);
}

// (*line_count)++ > -100 - just to increase line_count
int	get_textures_colors(t_cub *args, int *line_count, int *count, int *is_valid)
{
	char	*l;
	char	*t;
	char	**s;

	while ((*line_count)++ > -100 && *count != 6)
	{
		l = get_next_line(args->fd);
		if (l == NULL)
			break ;
		t = ft_strtrim(l, "\t\b ");
		s = ft_ssplit(l, " \t\n");
		if ((t == NULL || s == NULL) && fr(l, t, s) == 0)
			return (10);
		if (split_count(s) == 0 && fr(l, t, s) == 0)
			continue ;
		*is_valid = is_valid_str(l, s, args);
		if (*is_valid == 10)
			return (10);
		else if (*is_valid == 1)
			(*count)++;
		else if ((ft_strcmp(t, "\n") != 0 && *count != 6) && fr(l, t, s) == 0)
			return (1);
		fr(l, t, s);
	}
	return (*count != 6);
}
