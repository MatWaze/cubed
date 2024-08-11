/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:56:23 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/10 17:16:23 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>

#include "common/common.h"
#include "incs/t_cub.h"

int		get_map(t_cub *cubed, int *line_count);
int		get_textures_colors(t_cub *args, int *line_count);
void	set_cubed(t_cub *cubed, char *name);

void	set_cubed(t_cub *cubed, char *name)
{
	cubed->name = name;
	cubed->col_sides.north_found = 0;
	cubed->col_sides.south_found = 0;
	cubed->col_sides.west_found = 0;
	cubed->col_sides.east_found = 0;
	cubed->col_sides.floor_found = 0;
	cubed->col_sides.ceiling_found = 0;
}

int	validation(char *filename, t_cub *cubed)
{
	int	ans;
	int	l_count;

	ans = 0;
	l_count = 0;
	cubed->fd = open(filename, O_RDONLY);
	if (check_file(&cubed->fd) == 0)
	{
		set_cubed(cubed, filename);
		ans = get_textures_colors(cubed, &l_count);
		if (ans == 1)
			printf("Error with texture(s) or color(s).\n");
		else
		{
			printf("Check for map errors.\n");
			ans = get_map(cubed, &l_count);
			if (ans == 1)
				printf("Error with map\n");
		}
	}
	return (ans);
}
