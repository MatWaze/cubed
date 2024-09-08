/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:56:23 by mamazari          #+#    #+#             */
/*   Updated: 2024/09/08 21:36:16 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "common/common.h"
#include "error/codes.h"
#include "error/error.h"
#include "t_cub.h"
#include "error/t_err.h"
#include <stdlib.h>	
char	*convert_line(char *line);
void	tab_to_space(char *line, char *new_line);
void	skip_empty(int fd, char **line);
char	**init_map(char *name, int *line_count, int* i);
int		get_textures_colors(t_cub *args, int *line_count);
int		is_map_valid(t_cub *cubed);
void	set_cubed(t_cub *cubed, char *name);

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

int	get_map(t_cub *cubed, int *line_count, char *new_line, char *line)
{
	int		i;

	cubed->map = init_map(cubed->name, line_count, &i);
	if (cubed->map)
	{
		skip_empty(cubed->fd, &line);
		while (line)
		{
			printf("i: %i, %s", i, line);
			new_line = ft_strtrim(line, "\n");
			if (free_return(line) && !new_line)
				return (10);
			line = convert_line(new_line);
			if (free_return(new_line) && !line)
				return (10);
			cubed->map[i] = ft_strdup(line);
			if (free_return(line) && cubed->map[i++] == NULL && free_arr(cubed->map))
				return (10);
			line = get_next_line(cubed->fd);
		}
		printf("i: %d\n", i);
		cubed->map[i] = NULL;
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
		ans = get_textures_colors(cubed, &l_count);
		if (check_err(err, ans != 10, C3D_ALL))
		{
			if (check_err(err, ans != 1, PARSING_TEXTURE_COLOR))
			{
				ans = get_map(cubed, &l_count, new_line, line);
				if (check_err(err, ans != 10, C3D_ALL))
					ans = is_map_valid(cubed);
				if (check_err(err, ans == 0, PARSING_MAP))
					printf("no err\n");
			}
		}
		untrack(err);
	}
	close(cubed->fd);
	return (ans);
}
