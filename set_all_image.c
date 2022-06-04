/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_all_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:27:54 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/27 16:24:11 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>

void	set_player_variable(t_player *player, t_map *map, int x, int y)
{
	player->x = x * IMG_SIZE;
	player->y = y * IMG_SIZE;
	player->previous_x = x;
	player->previous_y = y;
	player->nb_move = 0;
	player->sleep = IDLE_ANIM_TX / (map->nb_columns * map->nb_lines);
	player->speed = SPEED * map->nb_columns * map->nb_lines;
	if (player->speed > 2)
		player->speed = 2;
}

void	set_player_postion(t_map *map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->nb_lines)
	{
		x = 0;
		while (x < map->nb_columns)
		{
			if (map->map[y][x] == 'P')
			{
				set_player_variable(player, map, x, y);
				return ;
			}
			x ++;
		}
		y ++;
	}
}

int	set_map_image(t_data **all_image, t_game *game,
						const char **path, int count)
{
	int	i;

	(void)game;
	(void)path;
	i = -1;
	while (++i < count)
	{
		(*all_image)[i].img = mlx_xpm_file_to_image(game->vars.mlx,
				(char *)path[i], &(*all_image)[i].width,
				&(*all_image)[i].height);
		if (!(*all_image)[i].img)
			return (-3);
		(*all_image)[i].addr = mlx_get_data_addr((*all_image)[i].img,
				&(*all_image)[i].bits_per_pixel, &(*all_image)[i].line_length,
				&(*all_image)[i].endian);
		if (!(*all_image)[i].addr)
		{
			mlx_destroy_image(game->vars.mlx, (*all_image)[i].img);
			return (-3);
		}
	}
	return (0);
}
