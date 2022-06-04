/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:40:30 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 19:15:01 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "libft/libft.h"
#include "mlx_linux/mlx.h"
#include <math.h>

int	check_case(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i ++;
	}
	return (0);
}

int	check_ground_monster_y(float x, float y, char **map, char *allowed_case)
{
	int	pos_x;
	int	pos_y;

	pos_x = floor(x / IMG_SIZE);
	pos_y = floor(y / IMG_SIZE);
	if (!check_case(map[pos_y][pos_x], allowed_case))
		return (0);
	if (!check_case(map[pos_y + 1][pos_x], allowed_case))
		return (0);
	return (1);
}

int	check_ground_monster_x(float x, float y, char **map, char *allowed_case)
{
	int	pos_x;
	int	pos_y;

	pos_x = floor(x / IMG_SIZE);
	pos_y = floor(y / IMG_SIZE);
	if (!check_case(map[pos_y][pos_x], allowed_case))
		return (0);
	if (!check_case(map[pos_y][pos_x + 1], allowed_case))
		return (0);
	return (1);
}

int	check_ground(float x, float y, char **map, char *allowed_case)
{
	int	pos_x;
	int	pos_y;

	pos_x = floor(x / IMG_SIZE);
	pos_y = floor(y / IMG_SIZE);
	if (!check_case(map[pos_y][pos_x], allowed_case))
		return (0);
	if ((int)floor(x) % 32 != 0 && !check_case(map[pos_y][pos_x + 1],
		allowed_case))
		return (0);
	if ((int)floor(y) % 32 != 0 &&!check_case(map[pos_y + 1][pos_x],
		allowed_case))
		return (0);
	if ((int)floor(x) % 32 != 0 && (int)floor(y) % 32 != 0
		&& !check_case(map[pos_y + 1][pos_x + 1], allowed_case))
		return (0);
	return (1);
}

int	check_collision_monster(t_game *game)
{
	int	i;
	int	diff_x;
	int	diff_y;

	i = 0;
	while (i < game->map.count_monster)
	{
		diff_x = fabsf(game->monster[i].x - game->player.x);
		diff_y = fabsf(game->monster[i].y - game->player.y);
		if (diff_x < COLL_BOX && diff_y < COLL_BOX)
			return (0);
		i ++;
	}
	return (1);
}
