/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:56:23 by mamazari          #+#    #+#             */
/*   Updated: 2024/09/10 17:11:29 by mamazari         ###   ########.fr       */
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
void	valid_check(t_cub *cubed, t_err *err, int l_count, int *count);
void	set_cubed(t_cub *cubed, char *name);

int	empty_check(char **map)
{
	int		i;
	int		ans;
	char	*trim;

	i = 0;
	ans = 0;
	while (map[i])
	{
		trim = ft_strtrim(map[i], " ");
		if (trim == NULL)
			return (10);
		if (ft_strlen(trim) == 0)
		{
			free(trim);
			ans = 1;
			break ;
		}
		free(trim);
		i++;
	}
	return (ans);
}

int	set_to_null(char **map, int i)
{
	map[i] = NULL;
	return (1);
}

int	get_map(t_cub *cub, int *line_count, char *n_line, char *line)
{
	int		i;

	cub->map = init_map(cub->name, line_count, &i);
	if (cub->map)
	{
		line = get_next_line(cub->fd);
		skip_empty(cub->fd, &line);
		while (line)
		{
			n_line = ft_strtrim(line, "\n");
			if (free_return(line) && !n_line && set_to_null(cub->map, i))
				return (10);
			line = convert_line(n_line);
			if (free_return(n_line) && !line && && set_to_null(cub->map, i))
				return (10);
			cub->map[i] = ft_strdup(line);
			if (free_return(line) && !cub->map[i] && && set_to_null(cub->map, i))
				return (10);
			line = get_next_line(cub->fd);
			i++;
		}
		cub->map[i] = NULL;
		return (1);
	}
	return (10);
}

int	validation(char *filename, t_cub *cubed, t_err *err)
{
	int		ans;
	int		count;
	int		l_count;
	char	*line;
	char	*new_line;

	ans = 0;
	count = 0;
	l_count = 0;
	cubed->fd = open(filename, O_RDONLY);
	if (track(err, "validation") && \
		check_err(err, check_file(&cubed->fd) == 0, PARSING_FILE_NOT_OPEN))
	{
		line = NULL;
		new_line = NULL;
		set_cubed(cubed, filename);
		valid_check(cubed, err, l_count, &count);
		untrack(err);
	}
	close(cubed->fd);
	return (ans);
}

void	valid_check(t_cub *cubed, t_err *err, int l_count, int *count)
{
	int		ans;
	int		is_valid;

	ans = get_textures_colors(cubed, &l_count, count, &is_valid);
	if (track(err, "valid_check") && check_err(err, ans != 10, C3D_ALL))
	{
		if (check_err(err, ans != 1, PARSING_TEXTURE_COLOR))
		{
			ans = get_map(cubed, &l_count, NULL, NULL);
			if (track(err, "get_map") && check_err(err, ans != 10, C3D_ALL) \
			&& check_err(err, empty_check(cubed->map) != 1, EMPTY_LINE) \
			&& check_err(err, empty_check(cubed->map) != 10, C3D_ALL))
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
