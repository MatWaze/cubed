/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:30:01 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/10 10:55:46 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include "parsing/parsing.h"
#include "common/common.h"
#include "libft/libft.h"

void	set_cubed(t_cub *cubed)
{
	cubed->col_sides.north_found = 0;
	cubed->col_sides.south_found = 0;
	cubed->col_sides.west_found = 0;
	cubed->col_sides.east_found = 0;
	cubed->col_sides.floor_found = 0;
	cubed->col_sides.ceiling_found = 0;
}

int	main1(int argc, char **argv)
{
	int		ans;
	t_cub	cubed;

	ans = 0;
	if (argc == 2)
	{
		cubed.fd = open(argv[1], O_RDONLY);
		if (check_file(&cubed.fd) == 0)
		{
			set_cubed(&cubed);
			ans = get_textures_colors(&cubed);
			if (ans == 1)
				printf("Error with texture(s) or color(s).\n");
			else
			{
				printf("No error with textures and colors.\n");
			}
		}
	}
	else
		printf("Usage: ./cub3d path_to_cub_file\n");
	return (ans);
}

int	main(int argc, char **argv)
{
	main1(argc, argv);
	system("leaks cub3d");
}
