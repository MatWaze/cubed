/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:30:01 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/09 11:37:24 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>

#include "parsing/parsing.h"
#include "common/common.h"
#include "libft/libft.h"

int	main(int argc, char **argv)
{
	int		ans;
	t_cub	cubed;

	ans = 0;
	if (argc == 2)
	{
		cubed.fd = open(argv[1], O_RDONLY);
		if (check_file(&cubed.fd) == 0)
		{
			ans = get_textures_colors(&cubed);
			if (ans == 1)
				printf("Error with texture(s) or color(s).\n");
			else
			{
				// map check
			}
		}
	}
	else
		printf("Usage: ./cub3d path_to_cub_file\n");
	return (ans);
}
