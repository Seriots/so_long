/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 00:53:06 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 20:25:12 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "include/so_long.h"

char	**ft_free_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	return (0);
}

t_map	set_error(int *error, int code, t_map map)
{
	*error = code;
	return (map);
}

int	ft_count_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	free(line);
	while (line)
	{
		count ++;
		line = get_next_line(fd);
		free(line);
	}
	return (count);
}

int	ft_print_error(int code)
{
	if (code == -1)
		ft_putstr_fd("Error\n-One argument is required\n", STDERR_FILENO);
	else if (code == -2)
		ft_putstr_fd("Error\n-Invalid file\n", STDERR_FILENO);
	else if (code == -3)
		ft_putstr_fd("Error\n-Malloc error\n", STDERR_FILENO);
	else if (code == -4)
		ft_putstr_fd("Error\n-Empty map\n", STDERR_FILENO);
	else if (code == -5)
		ft_putstr_fd("Error\n-The map must be a rectangle\n", STDERR_FILENO);
	else if (code == -6)
		ft_putstr_fd("Error\n-The map must be enclosed\n", STDERR_FILENO);
	else if (code == -7)
		ft_putstr_fd("Error\n-The map need at least one item\n", STDERR_FILENO);
	else if (code == -8)
		ft_putstr_fd("Error\n-The map need at least one exit\n", STDERR_FILENO);
	else if (code == -9)
		ft_putstr_fd("Error\n-The map must contains one player\n", STDERR_FILENO);
	else if (code == -10)
		ft_putstr_fd("Error\n-Invalid character\n", STDERR_FILENO);
	else if (code == -11)
		ft_putstr_fd("Error\n-Only '.ber' map are allowed\n", STDERR_FILENO);
	else if (code == -12)
		ft_putstr_fd("Error\nMlx Error\n", STDERR_FILENO);
	return (0);
}

void	set_map_struct(t_map *map)
{
	map->exit = 0;
	map->player = 0;
	map->items = 0;
	map->nb_lines = 0;
	map->nb_columns = 0;
	map->map = 0;
	map->count_monster = 0;
}
