/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 07:45:33 by zanikin           #+#    #+#             */
/*   Updated: 2024/09/08 21:35:17 by mamazari         ###   ########.fr       */
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
# define C3D_MAIN_INV_PARAM_DESK "Usage: cub3D path_to_cub_file"
# define PARSING_FILE_NOT_OPEN 10
# define PARSING_FILE_NOT_OPEN_DESK "Can't open a file"
# define PARSING_TEXTURE_COLOR 11
# define PARSING_TEXTURE_COLOR_DESK "Error with texture(s) or color(s)"
# define PARSING_MAP 12
# define PARSING_MAP_DESK "Error with map"
# define MAIN_INV_FILE_NAME 13
# define MAIN_INV_FILE_NAME_DESK "Not a .cub file"

#endif
