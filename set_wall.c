/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:14:25 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 19:30:11 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	set_wall(t_map *map)
{
	int	i;

	i = 0;
	map->map[0][0] = '6';
	map->map[0][map->nb_columns - 1] = '7';
	map->map[map->nb_lines - 1][0] = '8';
	map->map[map->nb_lines - 1][map->nb_columns - 1] = '9';
	while (++i < map->nb_columns - 1)
		map->map[0][i] = '2';
	i = 0;
	while (++i < map->nb_columns - 1)
		map->map[map->nb_lines - 1][i] = '3';
	i = 0;
	while (++i < map->nb_lines - 1)
		map->map[i][0] = '4';
	i = 0;
	while (++i < map->nb_lines - 1)
		map->map[i][map->nb_columns - 1] = '5';
}
