/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 00:46:34 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/25 15:59:56 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"
#include "include/so_long.h"
#include "include/parsing.h"

t_map	ft_set_map(t_map *map, int *error, char *path)
{
	int		fd;
	int		i;

	i = -1;
	map->map = (char **)malloc(sizeof(char *) * (map->nb_lines + 1));
	if (!map->map)
		return (set_error(error, -3, *map));
	map->map[map->nb_lines] = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free(map->map);
		return (set_error(error, -2, *map));
	}
	while (++i < map->nb_lines)
	{
		map->map[i] = get_next_line(fd);
		if (!ft_strlen(map->map[i]))
			return (set_error(error, -2, *map));
	}
	close(fd);
	return (*map);
}

void	check_case_value(t_map *map, int x, int y, int *error)
{
	if (map->map[y][x] == 'C')
		map->items ++;
	else if (map->map[y][x] == 'E')
		set_exit(map, x, y);
	else if (map->map[y][x] == 'P')
	{
		if (map->player == 1)
			map->map[y][x] = '0';
		else
			map->player ++;
	}
	else if (map->map[y][x] == 'W' || map->map[y][x] == 'X'
			|| map->map[y][x] == 'Y' || map->map[y][x] == 'Z')
		map->count_monster++;
	else if (map->map[y][x] != '0' && map->map[y][x] != '1')
	{
		map->map = ft_free_map(map->map);
		*error = -10;
	}
}

int	ft_init_map_params(t_map *map, int x, int y, int *error)
{
	if ((x == 0 || y == 0 || x == map->nb_columns - 1 || y == map->nb_lines - 1)
		&& map->map[y][x] != '1')
	{
		map->map = ft_free_map(map->map);
		*error = -6;
		return (0);
	}
	check_case_value(map, x, y, error);
	if (*error < 0)
		return (0);
	return (1);
}

int	ft_check_map(int *error, t_map *map)
{
	int	x;
	int	y;
	int	len_next;

	map->nb_columns = ft_strlen(map->map[0]);
	y = -1;
	while (++y < map->nb_lines)
	{
		x = -1;
		len_next = ft_strlen(map->map[y]);
		if (map->nb_columns != len_next)
		{
			*error = -5;
			map->map = ft_free_map(map->map);
			return (0);
		}
		while (++x < map->nb_columns)
			if (!ft_init_map_params(map, x, y, error))
				return (0);
	}
	if (!ft_check_map_params(map, error))
		return (0);
	return (1);
}

t_map	ft_parsing_map(int argc, char *argv[], int *error)
{
	t_map	map;
	int		fd;

	set_map_struct(&map);
	if (argc != 2)
		return (set_error(error, -1, map));
	if (ft_strlen(argv[1]) < 5)
		return (set_error(error, -1, map));
	if (!check_end(argv[1]))
		return (set_error(error, -11, map));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (set_error(error, -2, map));
	map.nb_lines = ft_count_lines(fd);
	if (map.nb_lines <= 0)
		return (set_error(error, -4, map));
	close(fd);
	map = ft_set_map(&map, error, argv[1]);
	if (!map.map || *error < 0)
		return (map);
	if (!ft_check_map(error, &map))
		return (map);
	set_wall(&map);
	return (set_error(error, 0, map));
}
