/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:30:01 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/15 00:52:28 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#include "error/error.h"
#include "error/codes.h"
#include "c3d_math/c3d_math.h"
#include "parsing/parsing.h"
#include "common/common.h"
#include "libft/libft.h"

int	main(int argc, char **argv)
{
	//t_cub			cubed;
	t_mat			map;
	static t_err	err = {0};
	unsigned int	i;
	unsigned int	j;

	(void)argv;
	if (track(&err, "main") && check_err(&err, argc == 2, C3D_MAIN_INV_PARAM)
			&& create_mat(&map, 5, 5, &err))
	{
		i = 0;
		while (i < map.h)
		{
			j = 0;
			while (j < map.w)
			{
				map.m[i][j] = j + i * map.w;
				j += 1;
			}
			i += 1;
		}
		i = 0;
		while (i < map.h)
		{
			j = 0;
			while (j < map.w)
				printf("%c ", map.m[i][j++] + '0');
			printf("\n");
			i += 1;
		}
		free(map.m);
		//validation(argv[1], &cubed);
		untrack(&err);
	}
	print_trace(&err);
	return (err.error);
}
