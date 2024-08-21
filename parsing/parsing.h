/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:29:34 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/10 12:07:51 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "t_cub.h"
# include "error/t_err.h"

int	validation(char *filename, t_cub *cubed, t_err *err);

#endif