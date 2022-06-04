/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 02:00:42 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 21:12:22 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include <math.h>

void	update_die_screen(t_game *game, t_data new_img)
{
	mlx_put_image_to_window(game->vars.mlx, game->vars.window,
		new_img.img, 0, 0);
	mlx_put_image_to_window(game->vars.mlx, game->vars.window,
		game->player.img.img, game->player.x, game->player.y);
	mlx_destroy_image(game->vars.mlx, new_img.img);
}

void	die_animation(t_game *game)
{
	t_data	new_img;

	if (game->player.sleep > 0)
		game->player.sleep --;
	else
	{
		redraw_player_case(game);
		game->player.current_img ++;
		if (game->player.current_img >= NB_ANIM_PLAYER_IMG)
			destroy_game_boom_explosion_all_clear(game, 0);
		if (game->player.current_img == NB_ANIM_MONSTER_IMG)
			game->player.sleep = DIE_ANIM_TX * 2;
		else
			game->player.sleep = DIE_ANIM_TX;
		game->player.img = game->player.all_player_img[game->player.state]
		[game->player.direction][game->player.current_img];
		new_img.img = mlx_new_image(game->vars.mlx,
				game->map.nb_columns * IMG_SIZE, game->map.nb_lines * IMG_SIZE);
		if (!new_img.img)
			return ;
		update_die_screen(game, new_img);
	}
}

void	exit_appear(t_game *game)
{
	game->map.map[game->map.exit_y][game->map.exit_x] = 'E';
	game->player.nb_items --;
	game->end = 1;
	game->allowed_case = "0CPEWXZY";
	set_image(&game->map_image, game->all_image[EXIT],
		game->map.exit_x, game->map.exit_y);
}

int	display(t_game *game)
{
	int	i;

	if (game->die)
		die_animation(game);
	else
	{
		update_map(game);
		if (game->player.nb_items == game->map.items)
			exit_appear(game);
		i = -1;
		while (++i < game->map.count_monster)
			update_monster(game, i);
		mlx_put_image_to_window(game->vars.mlx, game->vars.window,
			game->map_image.img, 0, 0);
	}
	return (0);
}
