/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:26:54 by mamazari          #+#    #+#             */
/*   Updated: 2024/10/10 17:11:39 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common/common.h"
#include "game/t_game.h"
#include "libft/libft.h"
#include "parsing/t_cub.h"
#include <stdlib.h>
#include <unistd.h>
#include "minilibx/mlx.h"

int	set_imgs(t_game *game)
{
	int	x;
	int	ans;

	x = 2;
	ans = 0;
	if (access("./textures/bl_11zon.xpm", R_OK) == 0 && access(\
	"./textures/pl_11zon.xpm", R_OK) == 0 && access("./textures/bg2_11zon.xpm", R_OK) == 0\
	&& access("./textures/door.xpm", R_OK) == 0 && access("./textures/open.xpm", \
	R_OK) == 0)
	{
		ans = 1;
		game->r.img_block = mlx_xpm_file_to_image(game->r.mlx, \
			"./textures/bl_11zon.xpm", &x, &x);
		game->r.img_pl = mlx_xpm_file_to_image(game->r.mlx, \
			"./textures/pl_11zon.xpm", &x, &x);
		game->r.img_bg = mlx_xpm_file_to_image(game->r.mlx, \
			"./textures/bg2_11zon.xpm", &x, &x);
		game->r.img_door = mlx_xpm_file_to_image(game->r.mlx, \
			"./textures/door.xpm", &x, &x);
		game->r.img_open = mlx_xpm_file_to_image(game->r.mlx, \
			"./textures/open.xpm", &x, &x);
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

void	put_image(t_game *game, int i, int j)
{
	int	x;
	int	y;

	x = game->ppos.x;
	y = game->map.h - 1 - (int)game->ppos.y;
	if (((x + j) >= 0 && (x + j) < (int) game->map.w) && ((y + i) >= 0 && \
		(y + i) < (int) game->map.h))
	{
		mlx_put_image_to_window(game->r.mlx, game->r.win, \
			game->r.img_bg, 50 + (10 * j), 50 + (10 * i));
		if (game->map.m[y + i][x + j] == '1')
			mlx_put_image_to_window(game->r.mlx, game->r.win, \
			game->r.img_block, 50 + (10 * j), 50 + (10 * i));
		else if (game->map.m[y + i][x + j] == 'D' /* && door closed */)
			mlx_put_image_to_window(game->r.mlx, game->r.win, \
			game->r.img_door, 50 + (10 * j), 50 + (10 * i));
		/* else if (game->map.m[y + i][x + j] == 'D' && door open) */
	}
}

void	draw_minimap(t_game *game)
{
	int		i;
	int		j;
	int		y;

	y = game->map.h - 1 - (int)game->ppos.y;
	i = -4;
	while (++i < 5)
	{
		j = -4;
		while (++j < 5)
			put_image(game, i, j);
	}
	mlx_put_image_to_window(game->r.mlx, game->r.win, game->r.img_pl, 50, 50);
}
