/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 07:45:33 by zanikin           #+#    #+#             */
/*   Updated: 2024/10/09 13:14:12 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODES_H
# define CODES_H

# define C3D_ERRNO -1
# define C3D_TRACE_TRACK_ALL 0
# define C3D_TRACE_TRACK_ALL_DESK "Trace tracker failed to allocate memory"
# define C3D_TRACE_PRINT_ALL 1
# define C3D_TRACE_PRINT_ALL_DESK "Trace printer failed to allocate memory"
# define C3D_ALL 2
# define C3D_ALL_DESK "Memory allocation failed"
# define C3D_INV_PAR 3
# define C3D_INV_PAR_DESK "Invalid parameters"
# define C3D_MAIN_INV_PARAM 4
# define MLX_INIT 5
# define MLX_INIT_DESK "minilibx failed initialization"
# define MLX_ALLOC 6
# define MLX_ALLOC_DESK "minilibx failed memory allocation"
# define MLX_ADDR 7
# define MLX_ADDR_DESK "Image's data address extraction failed"
# define C3D_MAIN_INV_PARAM_DESK "Usage: cub3D path_to_cub_file"
# define PARSING_FILE_NOT_OPEN 10
# define PARSING_FILE_NOT_OPEN_DESK "Can't open a file"
# define PARSING_TEXTURE_COLOR 11
# define PARSING_TEXTURE_COLOR_DESK "Error with texture(s) or color(s)"
# define PARSING_MAP 12
# define PARSING_MAP_DESK "Error with a map"
# define MAIN_INV_FILE_NAME 13
# define MAIN_INV_FILE_NAME_DESK "Not a .cub file"
# define EMPTY_LINE 14
# define EMPTY_LINE_DESK "Empty line in a map"
# define DOOR_ERR 15
# define DOOR_ERR_DESK "Door not in between walls"
# define MAP_CREAT 16
# define MAP_CREAT_DESK "Error creating map"

#endif
