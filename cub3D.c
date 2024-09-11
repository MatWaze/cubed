/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:30:01 by mamazari          #+#    #+#             */
/*   Updated: 2024/09/10 15:46:45 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "error/error.h"
#include "error/codes.h"
// #include "c3d_math/c3d_math.h"
#include "parsing/t_cub.h"
#include "parsing/parsing.h"
#include "libft/libft.h"
#include "common/common.h"
#include <stdio.h>

int	is_cub(char *filename)
{
	char	**strs;
	int		last;
	int		len;
	int		ans;

	strs = ft_split(filename, '/');
	last = split_count(strs) - 1;
	ans = 0;
	if (strs && strs[last])
	{
		len = ft_strlen(strs[last]);
		if (len > 4 && strs[last][len - 1] == 'b' \
		&& strs[last][len - 2] == 'u' && \
		strs[last][len - 3] == 'c' && strs[last][len - 4] == '.')
			ans = 1;
		free_arr(strs);
	}
	return (ans);
}

void	set_cubed(t_cub *cubed, char *name)
{
	cubed->map = NULL;
	cubed->name = name;
	cubed->col_sides.north = NULL;
	cubed->col_sides.south = NULL;
	cubed->col_sides.east = NULL;
	cubed->col_sides.west = NULL;
	cubed->col_sides.north_found = -1;
	cubed->col_sides.south_found = -1;
	cubed->col_sides.west_found = -1;
	cubed->col_sides.east_found = -1;
	cubed->col_sides.floor_found = -1;
	cubed->col_sides.ceiling_found = -1;
}

int	main2(int argc, char **argv)
{
	t_cub			cub;
	static t_err	err = {0};

	if (track(&err, "main") && check_err(&err, argc == 2, \
	C3D_MAIN_INV_PARAM) && check_err(&err, access(argv[1], X_OK) == 0, \
	PARSING_FILE_NOT_OPEN) && check_err(&err, is_cub(argv[1]) == 1, \
	MAIN_INV_FILE_NAME))
	{
		validation(argv[1], &cub, &err);
		if (cub.map)
			free_arr(cub.map);
		free_return(cub.col_sides.north) && free_return(cub.col_sides.south) \
		&& free_return(cub.col_sides.east) && free_return(cub.col_sides.west);
	}
	untrack(&err);
	print_trace(&err);
	return (err.error);
}

int	main(int argc, char **argv)
{
	main2(argc, argv);
	system("leaks cub3D");
	return (0);
}
