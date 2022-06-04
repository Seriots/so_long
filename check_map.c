/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:33:42 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 19:30:47 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "libft/libft.h"
#include "mlx_linux/mlx.h"
#include <math.h>

void	check_items(t_player *player, t_map *map)
{
	int	pos_x;
	int	pos_y;

	pos_x = (int)floor(player->x + IMG_SIZE / 2) / 32;
	pos_y = (int)floor(player->y + IMG_SIZE / 2) / 32;
	if (map->map[pos_y][pos_x] == 'C')
	{
		player->nb_items ++;
		map->map[pos_y][pos_x] = '0';
	}
}

void	check_exit(t_player *player, t_map *map, t_game *game)
{
	int	pos_x;
	int	pos_y;

	pos_x = (int)floor(player->x + IMG_SIZE / 2) / 32;
	pos_y = (int)floor(player->y + IMG_SIZE / 2) / 32;
	if (map->map[pos_y][pos_x] == 'E')
		destroy_game_boom_explosion_all_clear(game, 0);
}

int	check_movement(t_player *player)
{
	int	pos_x;
	int	pos_y;

	pos_x = (int)floor(player->x + IMG_SIZE / 2) / 32;
	pos_y = (int)floor(player->y + IMG_SIZE / 2) / 32;
	if (pos_x != player->previous_x || pos_y != player->previous_y)
	{
		player->previous_x = pos_x;
		player->previous_y = pos_y;
		player->nb_move += 1;
		return (1);
	}
	return (0);
}
