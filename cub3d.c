/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:30:01 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/10 19:00:28 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "parsing/parsing.h"
#include "common/common.h"
#include "libft/libft.h"

int	main1(int argc, char **argv)
{
	int		ans;
	t_cub	cubed;

	ans = 0;
	if (argc == 2)
	{
		validation(argv[1], &cubed);
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
