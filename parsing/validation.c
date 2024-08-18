/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:56:23 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/17 15:10:00 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>

#include "common/common.h"
#include "t_cub.h"

void	get_map(t_cub *cubed, int *line_count);
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
			get_map(cubed, &l_count);
			ans = is_map_valid(cubed);
			if (ans == 1)
				printf("Error with map\n");
			else
				printf("No problem.\n");
		}
	}
	else
		printf("Error opening file\n");
	return (ans);
}
