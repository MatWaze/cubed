/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:56:23 by mamazari          #+#    #+#             */
/*   Updated: 2024/09/09 20:25:41 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "common/common.h"
#include "error/codes.h"
#include "error/error.h"
#include "libft/libft.h"
#include "t_cub.h"
#include "error/t_err.h"
#include <stdlib.h>

char	*convert_line(char *line);
void	tab_to_space(char *line, char *new_line);
void	skip_empty(int fd, char **line);
char	**init_map(char *name, int *line_count, int *i);
int		get_textures_colors(t_cub *args, int *line_count, int *count, \
	int *is_valid);
int		is_map_valid(t_cub *cubed);
void	set_cubed(t_cub *cubed, char *name);
void	valid_check(t_cub *cubed, t_err *err, int l_count);

void	set_cubed(t_cub *cubed, char *name)
{
	cubed->name = name;
	cubed->col_sides.north_found = -1;
	cubed->col_sides.south_found = -1;
	cubed->col_sides.west_found = -1;
	cubed->col_sides.east_found = -1;
	cubed->col_sides.floor_found = -1;
	cubed->col_sides.ceiling_found = -1;
}

int	free_some(char ***map, int i)
{
	int	j;

	j = 0;
	if (*map)
	{
		while (j < i)
		{
			free_return(*map[j]);
			j++;
		}
		free(*map);
	}
	*map = NULL;
	return (1);
}

int	get_map(t_cub *cubed, int *line_count, char *new_line, char *line)
{
	int		i;

	cubed->map = init_map(cubed->name, line_count, &i);
	if (cubed->map)
	{
		line = get_next_line(cubed->fd);
		skip_empty(cubed->fd, &line);
		printf("line after skip_empty: %s\n", line);
		while (line)
		{
			new_line = ft_strtrim(line, "\n");
			printf("%s", line);
			if (free_return(line) && new_line == NULL)
				return (10);
			line = convert_line(new_line);
			if (free_return(new_line) && line == NULL)
				return (10);
			cubed->map[i] = ft_strdup(line);
			// printf("[%s]\n", line);
			if (free_return(line) && cubed->map[i] == NULL)
				return (10);
			line = get_next_line(cubed->fd);
			i++;
			// printf("%s", line);
		}
		cubed->map[i] = NULL;
		printf("\n\n");
		// for (int j = 0; cubed->map[j]; j++)
		// 	printf("[%s], [%zu]\n", cubed->map[j], ft_strlen(cubed->map[j]));
		return (1);
	}
	return (10);
}

int	validation(char *filename, t_cub *cubed, t_err *err)
{
	int		ans;
	int		l_count;
	char	*line;
	char	*new_line;

	ans = 0;
	l_count = 0;
	cubed->fd = open(filename, O_RDONLY);
	if (track(err, "validation") && \
		check_err(err, check_file(&cubed->fd) == 0, PARSING_FILE_NOT_OPEN))
	{
		line = NULL;
		new_line = NULL;
		set_cubed(cubed, filename);
		valid_check(cubed, err, l_count);
		untrack(err);
	}
	close(cubed->fd);
	return (ans);
}

void	valid_check(t_cub *cubed, t_err *err, int l_count)
{
	int		ans;
	char	*line;
	int		count;
	int		is_valid;
	char	*new_line;

	count = 0;
	ans = get_textures_colors(cubed, &l_count, &count, &is_valid);
	line = NULL;
	new_line = NULL;
	if (track(err, "valid_check") && \
		check_err(err, ans != 10, C3D_ALL))
	{
		if (check_err(err, ans != 1, PARSING_TEXTURE_COLOR))
		{
			ans = get_map(cubed, &l_count, new_line, line);
			if (track(err, "get_map") && \
				check_err(err, ans != 10, C3D_ALL))
			{
				ans = is_map_valid(cubed);
				if (check_err(err, ans != 10, C3D_ALL))
				{
					if (check_err(err, ans == 0, PARSING_MAP))
						printf("no err\n");
				}
				untrack(err);
			}
		}
		untrack(err);
	}
}
