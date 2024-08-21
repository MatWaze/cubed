/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:00:53 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/16 16:07:07 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "t_cub.h"
#include "libft/libft.h"
#include "common/common.h"
#include "error/error.h"
#include "error/codes.h"

int		nl_count(int fd, int l_count);
char	*convert_line(char *line);
void	tab_to_space(char *line, char *new_line);
void	skip_empty(int fd, char **line);

void	get_map(t_cub *cubed, int *line_count)
{
	char	*line;
	char	*new_line;
	char	**map;
	int		i;

	line = NULL;
	map = (char **) malloc(sizeof(char *) * \
	(nl_count(open(cubed->name, O_RDONLY), *line_count) + 2));
	if (map)
	{
		skip_empty(cubed->fd, &line);
		i = 0;
		while (line)
		{
			new_line = ft_strtrim(line, "\n");
			free_return(line);
			line = convert_line(new_line);
			free_return(new_line);
			map[i++] = ft_strdup(line);
			free_return(line);
			line = get_next_line(cubed->fd);
		}
		map[i] = NULL;
		cubed->map = map;
	}
}

int	nl_count(int fd, int l_count)
{
	char	*line;
	int		count;

	count = 1;
	line = get_next_line(fd);
	while (line)
	{
		if (l_count == 0 && count++)
			break ;
		else if (l_count != 0)
			l_count--;
		free(line);
		line = get_next_line(fd);
	}
	skip_empty(fd, &line);
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

char	*convert_line(char *line)
{
	int		i;
	int		count;
	char	*new_line;

	if (ft_strchr(line, '\t'))
	{
		i = -1;
		count = ft_strlen(line);
		while (line[++i])
		{
			if (line[i] == '\t')
				count += 3;
		}
		i = -1;
		new_line = (char *) malloc(sizeof(char) * (count + 1));
		tab_to_space(line, new_line);
	}
	else
		new_line = ft_strdup(line);
	return (new_line);
}

void	tab_to_space(char *line, char *new_line)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == '\t')
		{
			j = -1;
			while (++j < 4)
				new_line[k++] = ' ';
		}
		else
			new_line[k++] = line[i];
		i++;
	}
	new_line[k] = '\0';
}

void	skip_empty(int fd, char **line)
{
	char	*trim;

	free(*line);
	*line = get_next_line(fd);
	trim = ft_strtrim(*line, "\n\t ");
	while (*line && ft_strlen(trim) == 0)
	{
		free(*line);
		free(trim);
		*line = get_next_line(fd);
		trim = ft_strtrim(*line, "\n\t ");
	}
	free(trim);
}
