/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:26:54 by mamazari          #+#    #+#             */
/*   Updated: 2024/10/13 22:25:59 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common/common.h"
#include "error/error.h"
#include "game/game.h"
#include "game/t_game.h"
#include "libft/libft.h"
#include "parsing/t_cub.h"
#include <stdlib.h>
#include <unistd.h>
#include "minilibx/mlx.h"

int	set_imgs(t_game *game)
{
	int	ans;

	ans = 0;
	if (track(&game->e, "set_imgs"))
	{
		ans = 1;
		if (xpm_to_texture("textures/pl_11zon.xpm", game->r.mlx, \
		&game->r.img_pl, &game->e) && xpm_to_texture(\
		"./textures/bl_11zon.xpm", game->r.mlx, &game->r.img_block, \
		&game->e) && xpm_to_texture("textures/bg2_11zon.xpm", game->r.mlx, \
		&game->r.img_bg, &game->e) && xpm_to_texture("textures/door.xpm", \
		game->r.mlx, &game->r.img_door, &game->e) && xpm_to_texture(\
		"textures/open.xpm", game->r.mlx, &game->r.img_open, &game->e))
			untrack(&game->e);
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
	y = game->map->h - 1 - (int)game->ppos.y;
	if (((x + j) >= 0 && (x + j) < (int) game->map->w) && ((y + i) >= 0 && \
		(y + i) < (int) game->map->h))
	{
		mlx_put_image_to_window(game->r.mlx, game->r.win, \
			game->r.img_bg.img, 50 + (10 * j), 50 + (10 * i));
		if (game->map->m[y + i][x + j] == '1')
			mlx_put_image_to_window(game->r.mlx, game->r.win, \
			game->r.img_block.img, 50 + (10 * j), 50 + (10 * i));
		else if (game->map->m[y + i][x + j] == 'D' && \
			game->states.m[y + i][x + j] == 9)
			mlx_put_image_to_window(game->r.mlx, game->r.win, \
			game->r.img_open.img, 50 + (10 * j), 50 + (10 * i));
		else if (game->map->m[y + i][x + j] == 'D')
			mlx_put_image_to_window(game->r.mlx, game->r.win, \
			game->r.img_door.img, 50 + (10 * j), 50 + (10 * i));
	}
}

void	draw_minimap(t_game *game)
{
	int		i;
	int		j;
	int		y;

	y = game->map->h - 1 - (int)game->ppos.y;
	i = -4;
	while (++i < 5)
	{
		j = -4;
		while (++j < 5)
			put_image(game, i, j);
	}
	mlx_put_image_to_window(game->r.mlx, game->r.win, game->r.img_pl.img, \
		50, 50);
}
