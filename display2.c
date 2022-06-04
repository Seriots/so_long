/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:47:38 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/31 15:30:58 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "mlx_linux/mlx.h"
#include <math.h>

int	check_color_image(int color)
{
	if (color == 0 || color == 0x009C0000 || color == 0x003E0000
		|| color == 0x005E0000 || color == 0x007E0000
		|| color == 0x00403200 || color == 0x005C4800
		|| color == 0x00BA0000 || color == 0x00917200
		|| color == 0x00C79C00 || color == 0x00AD8800
		|| color == 0x00FFC800 || color == 0x00765D00
		|| color == 0x00FFDB5F)
		return (1);
	return (0);
}

void	my_mlx_put_image_to_window(t_game *game, t_data img, int x_g, int y_g)
{
	char			*dst;
	unsigned int	color;
	int				x;
	int				y;

	y = 0;
	while (y < IMG_SIZE)
	{
		x = 0;
		while (x < IMG_SIZE)
		{
			dst = img.addr + (y
					* img.line_length + x * (img.bits_per_pixel / 8));
			color = get_pxl_color(img, x, y);
			if (check_color_image(color))
				*(unsigned int *)dst = color;
			x++;
		}
		y ++;
	}
	mlx_put_image_to_window(game->vars.mlx, game->vars.window,
		img.img, x_g, y_g);
}

void	move_horizontal(t_game *game, int i)
{
	if (game->monster[i].direction == LEFT)
	{
		game->monster[i].direction = RIGHT;
		game->monster[i].movement = -game->monster[i].movement;
		game->monster[i].sleep = 0;
	}
	else
	{
		game->monster[i].direction = LEFT;
		game->monster[i].movement = -game->monster[i].movement;
		game->monster[i].sleep = 0;
	}
}

void	move_vertical(t_game *game, int i)
{
	if (game->monster[i].direction == FRONT)
	{
		game->monster[i].direction = BACK;
		game->monster[i].movement = -game->monster[i].movement;
		game->monster[i].sleep = 0;
	}
	else
	{
		game->monster[i].direction = FRONT;
		game->monster[i].movement = -game->monster[i].movement;
		game->monster[i].sleep = 0;
	}
}

void	update_monster(t_game *game, int i)
{
	if (game->monster[i].direction == LEFT
		|| game->monster[i].direction == RIGHT)
	{
		if (check_ground_monster_x(game->monster[i].x
				+ game->monster[i].movement, game->monster[i].y,
				game->map.map, "0PWXZY"))
			game->monster[i].x += game->monster[i].movement;
		else
			move_horizontal(game, i);
	}
	else
	{
		if (check_ground_monster_y(game->monster[i].x, game->monster[i].y
				+ game->monster[i].movement, game->map.map, "0PWXZY"))
			game->monster[i].y += game->monster[i].movement;
		else
			move_vertical(game, i);
	}
}
