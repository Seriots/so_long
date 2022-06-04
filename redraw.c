/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:15:37 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 19:18:07 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "mlx_linux/mlx.h"
#include <math.h>

void	redraw_player_case(t_game *game)
{
	int	x;
	int	y;

	x = (int)(floor(game->player.x) / IMG_SIZE);
	y = (int)(floor(game->player.y) / IMG_SIZE);
	set_image(&game->map_image,
		get_image(game, game->map.map[y][x]), x, y);
	set_image(&game->map_image,
		get_image(game, game->map.map[y][x + 1]), x + 1, y);
	set_image(&game->map_image,
		get_image(game, game->map.map[y + 1][x]), x, y + 1);
	set_image(&game->map_image,
		get_image(game, game->map.map[y + 1][x + 1]), x + 1, y + 1);
	set_image(&game->map_image,
		get_image(game, game->map.map[y - 1][x + 1]), x + 1, y - 1);
	set_image(&game->map_image,
		get_image(game, game->map.map[y + 1][x - 1]), x - 1, y + 1);
	set_image(&game->map_image,
		get_image(game, game->map.map[y][x - 1]), x - 1, y);
	set_image(&game->map_image,
		get_image(game, game->map.map[y - 1][x]), x, y - 1);
	set_image(&game->map_image,
		get_image(game, game->map.map[y - 1][x - 1]), x - 1, y - 1);
}

void	redraw_vertical_monster_case(t_game *game, int x, int y)
{
	set_image(&game->map_image,
		get_image(game, game->map.map[y + 1][x]), x, (y + 1));
	set_image(&game->map_image,
		get_image(game, game->map.map[y - 1][x]), x, (y - 1));
}

void	redraw_horizontal_monster_case(t_game *game, int x, int y)
{
	set_image(&game->map_image,
		get_image(game, game->map.map[y][x + 1]), (x + 1), y);
	set_image(&game->map_image,
		get_image(game, game->map.map[y][x - 1]), (x - 1), y);
}

void	redraw_monsters_case(t_game *game)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	while (i < game->map.count_monster)
	{
		x = (int)(floor(game->monster[i].x) / IMG_SIZE);
		y = (int)(floor(game->monster[i].y) / IMG_SIZE);
		set_image(&game->map_image,
			get_image(game, game->map.map[y][x]), x, y);
		if (game->monster[i].direction == LEFT
			|| game->monster[i].direction == RIGHT)
			redraw_horizontal_monster_case(game, x, y);
		else
			redraw_vertical_monster_case(game, x, y);
		i++;
	}
}
