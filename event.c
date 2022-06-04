/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:59:58 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/22 17:45:22 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "libft/libft.h"
#include "mlx_linux/mlx.h"
#include "include/parsing.h"

int	move(t_player *player, int *direction)
{
	if (player->move_top != 0 || &player->move_top == direction)
		player->move_top ++;
	if (player->move_bot != 0 || &player->move_bot == direction)
		player->move_bot ++;
	if (player->move_left != 0 || &player->move_left == direction)
		player->move_left ++;
	if (player->move_right != 0 || &player->move_right == direction)
		player->move_right ++;
	return (0);
}

int	stop_move(t_player *player, int *direction)
{
	int	n;

	n = *direction;
	*direction = 0;
	if (player->move_top > n)
		player->move_top --;
	if (player->move_bot > n)
		player->move_bot --;
	if (player->move_left > n)
		player->move_left --;
	if (player->move_right > n)
		player->move_right --;
	return (0);
}

int	close_request(t_game *game)
{
	destroy_game_boom_explosion_all_clear(game, 0);
	return (0);
}

int	key_released(int keycode, t_game *game)
{
	if (keycode == 65307)
		destroy_game_boom_explosion_all_clear(game, 0);
	else if (keycode == 119)
		stop_move(&game->player, &game->player.move_top);
	else if (keycode == 97)
		stop_move(&game->player, &game->player.move_left);
	else if (keycode == 100)
		stop_move(&game->player, &game->player.move_right);
	else if (keycode == 115)
		stop_move(&game->player, &game->player.move_bot);
	return (0);
}

int	key_pressed(int keycode, t_game *game)
{
	if (keycode == 65307)
		destroy_game_boom_explosion_all_clear(game, 0);
	else if (keycode == 119)
		move(&game->player, &game->player.move_top);
	else if (keycode == 97)
		move(&game->player, &game->player.move_left);
	else if (keycode == 100)
		move(&game->player, &game->player.move_right);
	else if (keycode == 115)
		move(&game->player, &game->player.move_bot);
	return (0);
}
