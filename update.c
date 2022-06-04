/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:21:35 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/31 15:30:45 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "libft/libft.h"
#include "mlx_linux/mlx.h"
#include <math.h>

void	update_sleep(t_game *game)
{
	if (game->player.sleep > 0)
		game->player.sleep --;
	else
	{
		if (game->player.state == IDLE)
			game->player.sleep = IDLE_ANIM_TX
				/ (game->map.nb_columns * game->map.nb_lines);
		else if (game->player.state == WALK)
			game->player.sleep = WALK_ANIM_TX
				/ (game->map.nb_columns * game->map.nb_lines);
		else
			game->player.sleep = DIE_ANIM_TX;
		game->player.img = change_img(&game->player.current_img,
				game->player.all_player_img[game->player.state]
			[game->player.direction], NB_ANIM_PLAYER_IMG - 1);
	}
}

void	update_monster_position(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.count_monster)
	{
		if (game->monster[i].sleep > 0)
			game->monster[i].sleep --;
		else
		{
			game->monster[i].sleep = MONSTER_ANIM_TX
				/ (game->map.nb_columns * game->map.nb_lines);
			game->monster[i].img = change_img(&game->monster[i].current_img,
					game->all_monster_img[game->monster[i].direction],
					NB_ANIM_MONSTER_IMG - 1);
		}
		put_object(&game->map_image, game->monster[i].img, game->monster[i].x,
			game->monster[i].y);
		i++;
	}
}

void	update_movement_counter(t_game *game)
{
	int		i;
	char	*count;

	if (check_movement(&game->player))
		ft_printf("move count = %d\n", game->player.nb_move);
	count = ft_itoa(game->player.nb_move);
	i = -1;
	while (count[++i] && i < game->map.nb_columns)
		put_object(&game->map_image, get_image(game, game->map.map[0][i]),
			i * IMG_SIZE, 0);
	i = -1;
	while (count[++i])
		put_number(&game->map_image, game->all_number[count[i] - 48],
			5 + i * 12, 2);
	free(count);
}

void	setup_game_to_die(t_game *game)
{
	game->player.state = DIE;
	game->die = 1;
	game->player.current_img = 0;
	game->player.img = game->player.all_player_img[game->player.state]
	[game->player.direction][game->player.current_img];
	game->player.sleep = DIE_ANIM_TX;
}

int	update_map(t_game *game)
{
	check_move_player(&game->player, game->map.map, game->allowed_case);
	check_items(&game->player, &game->map);
	if (game->player.move_top || game->player.move_bot
		|| game->player.move_right || game->player.move_left)
		game->player.state = WALK;
	else
		game->player.state = IDLE;
	if (game->end)
		check_exit(&game->player, &game->map, game);
	redraw_player_case(game);
	redraw_monsters_case(game);
	update_sleep(game);
	update_monster_position(game);
	put_object(&game->map_image, game->player.img,
		game->player.x, game->player.y);
	update_movement_counter(game);
	if (!check_collision_monster(game))
		setup_game_to_die(game);
	return (0);
}
