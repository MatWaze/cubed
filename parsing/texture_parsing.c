/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:16:52 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/08 18:55:53 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "libft/libft.h"
#include "common/common.h"
#include "incs/t_color_sides.h"
#include "incs/t_cub.h"

int		check_textures(char **s, t_cub *args);
int		is_valid_str(char *line, char **s, t_cub *args);
int		check_colors(char *line, char **s, t_cub *args);
int		set_rgb(char *str, char **split_rgb, t_color_sides *col);

int	get_textures_colors(t_cub *args)
{
	int		count;
	char	*line;
	char	*trimmed_line;
	char	**split;

	count = 0;
	while (count != 6)
	{
		line = get_next_line(args->fd);
		if (line == NULL)
			break ;
		trimmed_line = ft_strtrim(line, "\t\b ");
		split = ft_ssplit(line, " \t\n");
		if (split && *split && is_valid_str(line, split, args) == 1)
			count++;
		else if (ft_strcmp(trimmed_line, "\n") != 0 && count != 6)
			return (1);
		free(line);
		free(trimmed_line);
		free_arr(split);
	}
	return (count != 6);
}

int	is_valid_str(char *line, char **s, t_cub *args)
{
	int		ans;
	char	*temp;

	ans = 0;
	temp = ft_strtrim(line, "\t\b ");
	if (check_textures(s, args) == 0 || \
		check_colors(ft_strnstr(temp, s[0], ft_strlen(s[0])), s, args) == 0)
		ans = 1;
	return (ans);
}

int	check_textures(char **s, t_cub *args)
{
	int	ans;

	ans = 1;
	if (((split_count(s) == 2) && (access(s[1], F_OK) == 0) && \
		(ft_strcmp(s[0], "NO") == 0 || ft_strcmp(s[0], "SO") == 0 \
		|| ft_strcmp(s[0], "WE") == 0 || ft_strcmp(s[0], "EA") == 0)))
	{
		printf("%s, %s\n", s[0], s[1]);
		ans = 0;
		if (ft_strcmp(s[0], "NO") == 0)
			args->col_sides.north = ft_strdup(s[1]);
		else if (ft_strcmp(s[0], "SO") == 0)
			args->col_sides.south = ft_strdup(s[1]);
		else if (ft_strcmp(s[0], "WE") == 0)
			args->col_sides.west = ft_strdup(s[1]);
		else if (ft_strcmp(s[0], "EA") == 0)
			args->col_sides.east = ft_strdup(s[1]);
	}
	return (ans);
}

int	check_colors(char *line, char **s, t_cub *args)
{
	int		ans;
	int		j;
	char	*temp;
	char	**split_rgb;

	ans = 1;
	j = 0;
	if (ft_strcmp(s[0], "F") == 0 || ft_strcmp(s[0], "C") == 0)
	{
		if (line + 1 != NULL)
		{
			split_rgb = ft_split(line + 1, ',');
			if (split_count(split_rgb) == 3)
			{
				while (j < 3)
				{
					temp = split_rgb[j];
					split_rgb[j++] = ft_strtrim(temp, "\t\n ");
					free(temp);
				}
				ans = set_rgb(s[0], split_rgb, &args->col_sides);
			}
		}
	}
	return (ans);
}

int	set_rgb(char *str, char **split_rgb, t_color_sides *col)
{
	int	i;
	int	ans;

	i = 0;
	ans = 3;
	while (split_rgb[i] && ft_str_is_numeric(split_rgb[i++]) == 1)
		ans--;
	if (ans == 0)
	{
		if (ft_strcmp(str, "F") == 0)
		{
			col->floor_color.red = ft_atoi(split_rgb[0]);
			col->floor_color.green = ft_atoi(split_rgb[1]);
			col->floor_color.blue = ft_atoi(split_rgb[2]);
		}
		else if (ft_strcmp(str, "C") == 0)
		{
			col->ceiling_color.red = ft_atoi(split_rgb[0]);
			col->ceiling_color.green = ft_atoi(split_rgb[1]);
			col->ceiling_color.blue = ft_atoi(split_rgb[2]);
		}
	}
	return (ans);
}
