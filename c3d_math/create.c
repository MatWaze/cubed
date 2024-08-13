/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 06:48:28 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/12 07:32:19 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "c3d_math.h"
#include "error/error.h"
#include "libft/libft.h"

bool create_mat(t_mat *mat, unsigned int w, unsigned int h, t_err *error)
{
	char *arr;

	arr = (char *)malloc(sizeof(char) * w * h);
}