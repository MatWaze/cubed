/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:30:01 by mamazari          #+#    #+#             */
/*   Updated: 2024/10/09 20:52:32 by zanikin          ###   ########.fr       */
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

// bool	test_level(t_game *game);
// void	free_game(t_render *r, t_mat *map, t_mat *states);

// int	main(int argc, char **argv)
// {
// 	static t_game	game = {.e = {0}, .r = {0}};
// 	int				tmp;

// 	(void)argv;
// 	game.r.mlx = mlx_init();
// 	if (track(&game.e, "main")
// 		&& check_err(&game.e, game.r.mlx != NULL, MLX_INIT)
// 		&& check_err(&game.e, argc == 2, C3D_MAIN_INV_PARAM)
// 		&& test_level(&game))
// 	{
// 		game.r.win = mlx_new_window(game.r.mlx, WIN_WIDTH, WIN_HEIGHT,
// 				"cub3D");
// 		game.r.img = mlx_new_image(game.r.mlx, WIN_WIDTH, WIN_HEIGHT);
// 		if (check_err(&game.e, game.r.win != NULL, MLX_ALLOC)
// 			&& check_err(&game.e, game.r.img != NULL, MLX_ALLOC))
// 		{
// 			game.r.img_buff = (int *)mlx_get_data_addr(game.r.img, &tmp,
// 					&tmp, &tmp);
// 			mlx_do_key_autorepeaton(game.r.mlx);
// 			mlx_hook(game.r.win, KeyPress, 0, key_hook, &game);
// 			mlx_hook(game.r.win, DestroyNotify, 0, exit_game, &game);
// 			mlx_loop_hook(game.r.mlx, mouse_look, &game);
// 			mlx_mouse_move(game.r.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
// 			mlx_mouse_hide();
// 			render(&game);
// 			mlx_loop(game.r.mlx);
// 		}
// 	}
// 	print_trace(&game.e);
// 	free_game(&game.r, &game.map, &game.states);
// 	return (game.e.error);
// }

bool	test_level(t_game *game, t_cub *cub)
{
	if (track(&game->e, "test_level"))
	{
		unsigned int	i;
		unsigned int	j;
		unsigned int	x;
		unsigned int	y;

		double	k;
		double	l;

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
		k = x + 0.5;
		l = (cub->mat.h - 1 - y + 0.5);
		game->map = cub->mat;
		game->ppos.x = k;
		game->ppos.y = l;
		game->prot.x = 0.0;
		game->prot.y = 1.0;
		game->cam.x = CAMERA_HALF_FOV_TAN;
		game->cam.y = 0.0;
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


// bool	test_level(t_game *game)
// {
// 	if (track(&game->e, "test_level") && create_mat(&game->map, 10, 6,
// 			&game->e))
// 	{
// 		memcpy(game->map.m[0], "1111111111", 10);
// 		memcpy(game->map.m[1], "1000000001", 10);
// 		memcpy(game->map.m[2], "1011111101", 10);
// 		memcpy(game->map.m[3], "1010000101", 10);
// 		memcpy(game->map.m[4], "1000000001", 10);
// 		memcpy(game->map.m[5], "1111111111", 10);
// 		game->ppos.x = 8.5;
// 		game->ppos.y = 1.5;
// 		game->prot.x = 0.0;
// 		game->prot.y = 1.0;
// 		game->cam.x = CAMERA_HALF_FOV_TAN;
// 		game->cam.y = 0.0;
// 		game->r.ceil_color = 0x6e5020;
// 		game->r.floor_color = 0xa68444;
// 		game->r.wall_sides[0].img = mlx_xpm_file_to_image(game->r.mlx,
// 				"textures/backrooms.xpm", &game->r.wall_sides[0].w,
// 				&game->r.wall_sides[0].h);
// 		game->r.wall_sides[1].img = mlx_xpm_file_to_image(game->r.mlx,
// 				"textures/pool.xpm", &game->r.wall_sides[1].w,
// 				&game->r.wall_sides[1].h);
// 		game->r.wall_sides[2].img = mlx_xpm_file_to_image(game->r.mlx,
// 				"textures/chess.xpm", &game->r.wall_sides[2].w,
// 				&game->r.wall_sides[2].h);
// 		game->r.wall_sides[3].img = mlx_xpm_file_to_image(game->r.mlx,
// 				"textures/tubes.xpm", &game->r.wall_sides[3].w,
// 				&game->r.wall_sides[3].h);
// 		if (check_err(&game->e, game->r.wall_sides[0].img != NULL, MLX_ALLOC)
// 			&& check_err(&game->e, game->r.wall_sides[1].img != NULL, MLX_ALLOC)
// 			&& check_err(&game->e, game->r.wall_sides[2].img != NULL, MLX_ALLOC)
// 			&& check_err(&game->e, game->r.wall_sides[3].img != NULL,
// 				MLX_ALLOC))
// 			untrack(&game->e);
// 	}
// 	return (!game->e.error);
// }


int	main(int argc, char **argv)
{
	main2(argc, argv);
	// system("leaks cub3D");
	return (0);
}
