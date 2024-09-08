/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:03:56 by mamazari          #+#    #+#             */
/*   Updated: 2024/09/08 21:35:02 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "libft/libft.h"

int	free_return(char *var)
{
	if (var != NULL)
	{
		free(var);
	}
	return (1);
}

int	free_arr(char **av)
{
	int	i;

	if (av)
	{
		i = 0;
		while (av[i] != NULL)
		{
			free(av[i]);
			i++;
		}
		free(av);
	}
	return (0);
}

int	check_file(int *fd)
{
	int	ans;

	ans = 0;
	if (*fd < 0)
	{
		close(*fd);
		ans = 1;
	}
	return (ans);
}

int	split_count(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_str_is_numeric(char *str)
{
	int	i;
	int	ans;

	i = 0;
	ans = 1;
	if (ft_strlen(str) == 0)
		ans = 0;
	else if (str)
	{
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
			{
				ans = 0;
				break ;
			}
			i++;
		}
	}
	return (ans);
}
