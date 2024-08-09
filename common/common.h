/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:04:41 by mamazari          #+#    #+#             */
/*   Updated: 2024/08/08 17:15:51 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

void	free_arr(char **av);
int		check_file(int *fd);
int		split_count(char **s);
int		ft_str_is_numeric(char *str);
#endif