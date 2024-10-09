/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:30:01 by mamazari          #+#    #+#             */
/*   Updated: 2024/10/09 16:03:49 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <string.h>
#include <Tk/X11/X.h>
#include <sys/fcntl.h>

#include "minilibx/mlx.h"
#include "error/error.h"
#include "error/codes.h"
#include "game/game.h"
#include "libft/libft.h"
#include "c3d_math/c3d_math.h"
#include "game/config.h"


#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "error/error.h"
#include "error/codes.h"
#include "parsing/t_cub.h"
#include "parsing/parsing.h"
#include "libft/libft.h"
#include "common/common.h"
#include <stdio.h>

bool	test_level(t_game *game);
void	free_game(t_render *r, t_mat *map, t_mat *states);

int	main(int argc, char **argv)
{
	static t_game	game = {.e = {0}, .r = {0}};
	int				tmp;

	(void)argv;
	game.r.mlx = mlx_init();
	if (track(&game.e, "main")
		&& check_err(&game.e, game.r.mlx != NULL, MLX_INIT)
		&& check_err(&game.e, argc == 2, C3D_MAIN_INV_PARAM)
		&& test_level(&game))
	{
		game.r.win = mlx_new_window(game.r.mlx, WIN_WIDTH, WIN_HEIGHT,
				"cub3D");
		game.r.img = mlx_new_image(game.r.mlx, WIN_WIDTH, WIN_HEIGHT);
		if (check_err(&game.e, game.r.win != NULL, MLX_ALLOC)
			&& check_err(&game.e, game.r.img != NULL, MLX_ALLOC))
		{
			game.r.img_buff = (int *)mlx_get_data_addr(game.r.img, &tmp,
					&tmp, &tmp);
			mlx_do_key_autorepeaton(game.r.mlx);
			mlx_hook(game.r.win, KeyPress, 0, key_hook, &game);
			mlx_hook(game.r.win, DestroyNotify, 0, exit_game, &game);
			mlx_loop_hook(game.r.mlx, mouse_look, &game);
			mlx_mouse_move(game.r.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
			mlx_mouse_hide();
			render(&game);
			mlx_loop(game.r.mlx);
		}
	}
	print_trace(&game.e);
	free_game(&game.r, &game.map, &game.states);
	return (game.e.error);
}

bool	test_level(t_game *game)
{
	if (track(&game->e, "test_level") && create_mat(&game->map, 18, 39,
			&game->e))
	{
		memcpy(game->map.m[0],	"111111111111111111111111111111111111111", 39);
		memcpy(game->map.m[1],	"100000000000000000000000000000000000001", 39);
		memcpy(game->map.m[2],	"101111110000000000000000000000000000001", 39);
		memcpy(game->map.m[3],	"101000010000000000000000000000000000001", 39);
		memcpy(game->map.m[4],	"100000000000000000000000000000000000001", 39);
		memcpy(game->map.m[5],	"100000000000000000000000000000000000001", 39);
		memcpy(game->map.m[6],	"100000000000000000000000000000000000001", 39);
		memcpy(game->map.m[7],	"100000000000000000000000000000000000001", 39);
		memcpy(game->map.m[8],	"100000000000000000000000000000000000001", 39);
		memcpy(game->map.m[9],	"100000000000000000000000000000000000001", 39);
		memcpy(game->map.m[10],	"100000000000000000000000000000000000001", 39);
		memcpy(game->map.m[11],	"100000000000000000000000000000000000001", 39);
		memcpy(game->map.m[12],	"100000000000000000000000000000000000001", 39);
		memcpy(game->map.m[13],	"100000000000000000000000000000000000001", 39);
		memcpy(game->map.m[14],	"100000000000000000000000000000000000001", 39);
		memcpy(game->map.m[15],	"100000000000000000000000000000000000001", 39);
		memcpy(game->map.m[16],	"100000000000000000000000000000000000001", 39);
		memcpy(game->map.m[17],	"100000000000000000000000000000000000001", 39);
		memcpy(game->map.m[18],	"111111111111111111111111111111111111111", 39);
		game->ppos.x = 8.5f;
		game->ppos.y = 1.5f;
		game->prot.x = 0.0f;
		game->prot.y = 1.0f;
		game->cam.x = CAMERA_HALF_FOV_TAN;
		game->cam.y = 0.0f;
		game->r.ceil_color = 0x6e5020;
		game->r.floor_color = 0xa68444;
		if (xpm_to_texture("textures/pool.xpm", game->r.mlx, game->r.wall_sides,
				&game->e) && xpm_to_texture("textures/tubes.xpm", game->r.mlx,
				game->r.wall_sides + 1, &game->e)
			&& xpm_to_texture("textures/backrooms.xpm", game->r.mlx,
				game->r.wall_sides + 2, &game->e)
			&& xpm_to_texture("textures/wall.xpm", game->r.mlx,
				game->r.wall_sides + 3, &game->e))
			untrack(&game->e);
	}
	return (ok(&game->e));
}

/*bool	test_level(t_game *game, t_cub *cub)
{
	if (track(&game->e, "test_level"))
	{
		unsigned int	i;
		unsigned int	j;
		unsigned int	x;
		unsigned int	y;

		float	k;
		float	l;

		i = 0;
		while (i < cub->mat.h)
		{
			j = 0;
			while (j < cub->mat.w)
			{
				if (cub->mat.m[i][j] == 'E' || cub->mat.m[i][j] == 'N')
				{
					cub->mat.m[i][j] = '0';
					x = j;
					y = i;
					break ;
				}
				j++;
			}
			i++;
		}
		k = x + 0.5f;
		l = (cub->mat.h - 1 - y + 0.5f);
		game->map = cub->mat;
		game->ppos.x = k;
		game->ppos.y = l;
		game->prot.x = 0.0f;
		game->prot.y = 1.0f;
		game->cam.x = CAMERA_HALF_FOV_TAN;
		game->cam.y = 0.0f;
		game->r.ceil_color = 0x6e5020;
		game->r.floor_color = 0xa68444;
		game->r.wall_sides[NORTH].img = mlx_xpm_file_to_image(game->r.mlx,
				cub->col_sides.north, &game->r.wall_sides[NORTH].w,
				&game->r.wall_sides[NORTH].h);
		game->r.wall_sides[WEST].img = mlx_xpm_file_to_image(game->r.mlx,
				cub->col_sides.west, &game->r.wall_sides[WEST].w,
				&game->r.wall_sides[WEST].h);
		game->r.wall_sides[SOUTH].img = mlx_xpm_file_to_image(game->r.mlx,
				cub->col_sides.south, &game->r.wall_sides[SOUTH].w,
				&game->r.wall_sides[SOUTH].h);
		game->r.wall_sides[EAST].img = mlx_xpm_file_to_image(game->r.mlx,
				cub->col_sides.east, &game->r.wall_sides[EAST].w,
				&game->r.wall_sides[EAST].h);
		if (check_err(&game->e, game->r.wall_sides[NORTH].img != NULL, \
		MLX_ALLOC) && check_err(&game->e, game->r.wall_sides[WEST].img != NULL, \
		MLX_ALLOC) && check_err(&game->e, game->r.wall_sides[SOUTH].img != \
		NULL, MLX_ALLOC) && check_err(&game->e, game->r.wall_sides[EAST].img \
		!= NULL, MLX_ALLOC))
			untrack(&game->e);
	}
	return (!game->e.error);
}

void	free_game(t_render *r, t_mat *map, t_mat *states)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (r->wall_sides[i].img)
			mlx_destroy_image(r->mlx, r->wall_sides[i].img);
		i += 1;
	}
	i = 0;
	while (i < DOOR_FRAMES_COUNT)
	{
		if (r->door_frames[i].img)
			mlx_destroy_image(r->mlx, r->door_frames[i].img);
		i += 1;
	}
	if (r->img)
		mlx_destroy_image(r->mlx, r->img);
	if (r->win)
		mlx_destroy_window(r->mlx, r->win);
	free_mat(map);
	free_mat(states);
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
	static t_cub	cub = {0};
	static t_err	err = {0};
	static t_game	game = {.e = {0}, .r = {0}};
	int				tmp;
	int				valid;

	valid = 0;
	(void)argv;
	game.r.mlx = mlx_init();
	if (track(&err, "main") && check_err(&err, argc == 2, \
	C3D_MAIN_INV_PARAM) && check_err(&err, access(argv[1], F_OK) == 0, \
	PARSING_FILE_NOT_OPEN) && check_err(&err, is_cub(argv[1]) == 1, \
	MAIN_INV_FILE_NAME))
	{
		valid = validation(argv[1], &cub, &err);
		if (valid == 25 && test_level(&game, &cub) && check_err(&game.e, game.r.mlx != \
		NULL, MLX_INIT) && check_err(&game.e, argc == 2, C3D_MAIN_INV_PARAM))
		{
			game.r.win = mlx_new_window(game.r.mlx, WIN_WIDTH, WIN_HEIGHT,
					"cub3D");
			game.r.img = mlx_new_image(game.r.mlx, WIN_WIDTH, WIN_HEIGHT);
			if (check_err(&game.e, game.r.win != NULL, MLX_ALLOC)
				&& check_err(&game.e, game.r.img != NULL, MLX_ALLOC))
			{
				game.r.img_buff = (int *)mlx_get_data_addr(game.r.img, &tmp,
						&tmp, &tmp);
				mlx_do_key_autorepeaton(game.r.mlx);
				mlx_hook(game.r.win, KeyPress, 0, key_hook, &game);
				mlx_hook(game.r.win, DestroyNotify, 0, exit_game, &game);
				mlx_loop_hook(game.r.mlx, mouse_look, &game);
				mlx_mouse_move(game.r.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
				mlx_mouse_hide();
				render(&game);
				mlx_loop(game.r.mlx);
			}
		}
	}
	if (cub.map)
		free_arr(cub.map);
	if (free_return(cub.col_sides.north) && \
	free_return(cub.col_sides.south) && free_return(cub.col_sides.east) \
	&& free_return(cub.col_sides.west))
		;
	untrack(&err);
	print_trace(&err);
	return (err.error);
}

int	main(int argc, char **argv)
{
	main2(argc, argv);
	// system("leaks cub3D");
	return (0);
}*/
