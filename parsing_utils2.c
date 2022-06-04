/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:11:34 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 17:23:12 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "include/parsing.h"
#include "libft/libft.h"

int	ft_check_map_params(t_map *map, int *error)
{
	if (map->items < 1)
	{
		map->map = ft_free_map(map->map);
		*error = -7;
		return (0);
	}
	if (map->exit < 1)
	{
		map->map = ft_free_map(map->map);
		*error = -8;
		return (0);
	}
	else if (map->player != 1)
	{
		map->map = ft_free_map(map->map);
		*error = -9;
		return (0);
	}
	return (1);
}

void	set_exit(t_map *map, int x, int y)
{
	if (map->exit != 1)
	{
		map->exit ++;
		map->exit_x = x;
		map->exit_y = y;
	}	
	map->map[y][x] = '0';
}

int	check_end(char *argv)
{
	if (argv[ft_strlen(argv) - 1] != 'r'
		|| argv[ft_strlen(argv) - 2] != 'e'
		|| argv[ft_strlen(argv) - 3] != 'b'
		|| argv[ft_strlen(argv) - 4] != '.')
		return (0);
	return (1);
}
