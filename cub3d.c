/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matevos <matevos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:30:01 by mamazari          #+#    #+#             */
/*   Updated: 2024/09/05 20:10:10 by matevos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "error/error.h"
#include "error/codes.h"
#include "c3d_math/c3d_math.h"
#include "parsing/t_cub.h"
#include "parsing/parsing.h"
#include "libft/libft.h"

int	main2(int argc, char **argv)
{
	t_cub			cubed;
	static t_err	err = {0};

	(void)argv;
	if (track(&err, "main") && check_err(&err, argc == 2, C3D_MAIN_INV_PARAM))
	{
		validation(argv[1], &cubed, &err);
		untrack(&err);
	}
	for (int i = 0; cubed.map[i]; i++)
		free(cubed.map[i]);
	free(cubed.map);
	free(cubed.col_sides.north);
	free(cubed.col_sides.south);
	free(cubed.col_sides.east);
	free(cubed.col_sides.west);
	print_trace(&err);
	return (err.error);
}

int main(int argc, char **argv)
{
	main2(argc, argv);
	system("leaks cub3D");
	return (0);
}