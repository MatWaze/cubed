/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:48:36 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/09 15:38:39 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "incs/t_cub.h"
#include "libft/libft.h"
#include "common/common.h"

void	check_textures(char **s, t_cub *args, int *res);
int		check_colors(char *line, char **s, t_cub *args);
int		set_rgb(char *str, char **split_rgb, t_cub *col);
void	set_colors(char *str, char **split_rgb, t_cub *col, int *ans);

int	is_valid_str(char *line, char **s, t_cub *args)
{
	int		ans;
	int		res;
	char	*temp;

	ans = 0;
	res = 0;
	if (((split_count(s) == 2) && (access(s[1], F_OK) == 0) && \
		((ft_strcmp(s[0], "NO") == 0 && args->col_sides.north_found \
		== 0) || (ft_strcmp(s[0], "SO") == 0 && \
		args->col_sides.south_found == 0) || (ft_strcmp(s[0], "WE") == 0 && \
		args->col_sides.west_found == 0) || (ft_strcmp(s[0], "EA") == 0 && \
		args->col_sides.east_found == 0))) || \
		((ft_strcmp(s[0], "F") == 0 && args->col_sides.floor_found == 0) || \
		(ft_strcmp(s[0], "C") == 0 && args->col_sides.ceiling_found == 0)))
	{
		temp = ft_strtrim(line, "\t\b ");
		check_textures(s, args, &res);
		if (res == 0 || \
			check_colors(ft_strnstr(temp, s[0], ft_strlen(s[0])), s, args) == 0)
			ans = 1;
		free(temp);
	}
	return (ans);
}

void	check_textures(char **s, t_cub *args, int *res)
{
	if (ft_strcmp(s[0], "NO") == 0)
	{
		args->col_sides.north = ft_strdup(s[1]);
		args->col_sides.north_found = 1;
	}
	else if (ft_strcmp(s[0], "SO") == 0)
	{
		args->col_sides.south = ft_strdup(s[1]);
		args->col_sides.south_found = 1;
	}
	else if (ft_strcmp(s[0], "WE") == 0)
	{
		args->col_sides.west = ft_strdup(s[1]);
		args->col_sides.west_found = 1;
	}
	else if (ft_strcmp(s[0], "EA") == 0)
	{
		args->col_sides.east = ft_strdup(s[1]);
		args->col_sides.east_found = 1;
	}
	else
		*res = 1;
}

int	check_colors(char *line, char **s, t_cub *args)
{
	int		ans;
	int		j;
	char	*temp;
	char	**split_rgb;

	ans = 1;
	j = 0;
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
			ans = set_rgb(s[0], split_rgb, args);
		}
		free_arr(split_rgb);
	}
	return (ans);
}

int	set_rgb(char *str, char **split_rgb, t_cub *col)
{
	int	i;
	int	ans;

	i = 0;
	ans = 3;
	while (split_rgb[i] && ft_str_is_numeric(split_rgb[i++]) == 1)
		ans--;
	if (ans == 0)
		set_colors(str, split_rgb, col, &ans);
	return (ans);
}

void	set_colors(char *str, char **split_rgb, t_cub *col, int *ans)
{
	int	red;
	int	green;
	int	blue;

	red = ft_atoi(split_rgb[0]);
	green = ft_atoi(split_rgb[1]);
	blue = ft_atoi(split_rgb[2]);
	if ((red < 0 || red > 255) || (green < 0 || green > 255) || \
	(blue < 0 || blue > 255))
		*ans = 1;
	if (ft_strcmp(str, "F") == 0)
	{
		col->col_sides.floor_color.red = red;
		col->col_sides.floor_color.green = green;
		col->col_sides.floor_color.blue = blue;
		col->col_sides.floor_found = 1;
	}
	else if (ft_strcmp(str, "C") == 0)
	{
		col->col_sides.ceiling_color.red = red;
		col->col_sides.ceiling_color.green = green;
		col->col_sides.ceiling_color.blue = blue;
		col->col_sides.ceiling_found = 1;
	}
}
