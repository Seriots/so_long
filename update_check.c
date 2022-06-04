/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:31:17 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 18:40:57 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "libft/libft.h"
#include "mlx_linux/mlx.h"
#include <math.h>

void	check_move_left(t_player *player, char **map, char *allowed_case)
{
	if (player->move_left == 1)
	{
		if (check_ground(player->x - player->speed, player->y,
				map, allowed_case))
			player->x -= player->speed;
		else
			player->x = floor(player->x);
		if (player->direction != LEFT)
		{
			player->direction = LEFT;
			player->sleep = 0;
			player->current_img = 0;
		}	
	}	
}

void	check_move_right(t_player *player, char **map, char *allowed_case)
{
	if (player->move_right == 1)
	{
		if (check_ground(player->x + player->speed, player->y,
				map, allowed_case))
			player->x += player->speed;
		else
			player->x = floor(player->x);
		if (player->direction != RIGHT)
		{
			player->direction = RIGHT;
			player->sleep = 0;
			player->current_img = 0;
		}	
	}	
}

void	check_move_top(t_player *player, char **map, char *allowed_case)
{
	if (player->move_top == 1)
	{
		if (check_ground(player->x, player->y - player->speed,
				map, allowed_case))
			player->y -= player->speed;
		else
			player->y = floor(player->y);
		if (player->direction != BACK)
		{
			player->direction = BACK;
			player->sleep = 0;
			player->current_img = 0;
		}	
	}	
}

void	check_move_bot(t_player *player, char **map, char *allowed_case)
{
	if (player->move_bot == 1)
	{
		if (check_ground(player->x, player->y + player->speed,
				map, allowed_case))
			player->y += player->speed;
		else
			player->y = floor(player->y);
		if (player->direction != FRONT)
		{
			player->direction = FRONT;
			player->sleep = 0;
			player->current_img = 0;
		}
	}	
}

void	check_move_player(t_player *player, char **map, char *allowed_case)
{
	check_move_bot(player, map, allowed_case);
	check_move_top(player, map, allowed_case);
	check_move_left(player, map, allowed_case);
	check_move_right(player, map, allowed_case);
}
