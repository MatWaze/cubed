/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:00:53 by mamazari          #+#    #+#             */
/*   Updated: 2024/09/25 16:56:02 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "libft/libft.h"
#include "common/common.h"

int		nl_count(int fd, int l_count);
char	*convert_line(char *line);
void	tab_to_space(char *line, char *new_line);
void	skip_empty(int fd, char **line);

char	**init_map(char *name, int *line_count, int *i)
{
	char	**map;
	int		nl_c;

	map = NULL;
	*i = 0;
	nl_c = nl_count(open(name, O_RDONLY), *line_count);
	*line_count = nl_c;
	if (*line_count > 0 && *line_count != 10)
	{
		map = (char **) malloc(sizeof(char *) * (*line_count));
	}
	return (map);
}

int	nl_count(int fd, int l_count)
{
	char	*line;
	int		count;

	count = -1;
	line = ft_strdup(" ");
	if (line == NULL)
		return (10);
	while (line)
	{
		if (l_count == 0 && ++count)
			break ;
		else if (l_count != 0)
			l_count--;
		free(line);
		line = get_next_line(fd);
	}
	skip_empty(fd, &line);
	while (line && free_return(line))
	{
		count++;
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
		if (new_line != NULL)
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

	trim = ft_strtrim(*line, "\n\t ");
	while (*line && ft_strlen(trim) == 0)
	{
		free_return(*line);
		free_return(trim);
		*line = get_next_line(fd);
		trim = ft_strtrim(*line, "\n\t ");
	}
	free_return(trim);
}
