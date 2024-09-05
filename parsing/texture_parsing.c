/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matevos <matevos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:16:52 by mamazari          #+#    #+#             */
/*   Updated: 2024/09/05 20:07:39 by matevos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "libft/libft.h"
#include "common/common.h"
#include "t_cub.h"

int		is_valid_str(char *line, char **s, t_cub *args);
int		free_mem(char *line, char *trim, char **split);

int	free_mem(char *line, char *trim, char **split)
{
	if (line != NULL)
	{
		free(line);
		line = NULL;
	}
	if (trim != NULL)
	{
		free(trim);
		trim = NULL;
	}
	if (split != NULL)
	{
		free_arr(split);
		split = NULL;
	}
	return (0);
}

int	get_textures_colors(t_cub *args, int *line_count)
{
	int		count;
	char	*line;
	char	*trim;
	char	**split;

	count = 0;
	while (count != 6)
	{
		(*line_count)++;
		line = get_next_line(args->fd);
		if (line == NULL)
			break ;
		trim = ft_strtrim(line, "\t\b ");
		split = ft_ssplit(line, " \t\n");
		if (split_count(split) == 0 && free_mem(line, trim, split) == 0)
			continue ;
		else if (is_valid_str(line, split, args) == 1)
			count++;
		else if ((ft_strcmp(trim, "\n") != 0 && count != 6) \
			&& free_mem(line, trim, split) == 0)
			return (1);
		free_mem(line, trim, split);
	}
	return (count != 6);
}

