/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 00:41:17 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 21:17:59 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include "include/so_long.h"
#include "include/parsing.h"

void	init_game_variable(t_game *game)
{
	game->end = 0;
	game->monster = 0;
	game->all_monster_img = 0;
	game->all_image = 0;
	game->all_number = 0;
	game->allowed_case = "0CPWXYZ";
	game->player.all_player_img = 0;
	game->player.nb_items = 0;
	game->player.move_top = 0;
	game->player.move_bot = 0;
	game->player.move_left = 0;
	game->player.move_right = 0;
	game->player.sleep = IDLE_ANIM_TX * SPEED;
	game->player.state = IDLE;
	game->player.direction = FRONT;
	game->player.current_img = 0;
	game->die = 0;
}

void	init_game_image(t_game *game, int width, int height, t_data *img)
{
	img->img = mlx_new_image(game->vars.mlx, width, height);
	if (!img->img)
	{
		mlx_destroy_window(game->vars.mlx, game->vars.window);
		mlx_destroy_display(game->vars.mlx);
		free(game->vars.mlx);
		mlx_crash(&game->map);
	}
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(game->vars.mlx, img->img);
		mlx_destroy_window(game->vars.mlx, game->vars.window);
		mlx_destroy_display(game->vars.mlx);
		free(game->vars.mlx);
		mlx_crash(&game->map);
	}
	img->width = width;
	img->height = height;
}

void	call_hook(t_game *game)
{
	mlx_hook(game->vars.window, 2, 1L << 0, key_pressed, game);
	mlx_hook(game->vars.window, 3, 1L << 1, key_released, game);
	mlx_hook(game->vars.window, 33, 1L << 24, close_request, game);
	mlx_loop_hook(game->vars.mlx, display, game);
	mlx_do_sync(game->vars.mlx);
	mlx_loop(game->vars.mlx);
}

void	ft_init_game(t_game *game, int *error)
{
	game->all_image = load_all_image(game, error);
	if (*error < 0)
		destroy_game_boom_explosion_all_clear(game, *error);
	game->all_number = load_all_number(game, error);
	if (*error < 0)
		destroy_game_boom_explosion_all_clear(game, *error);
	game->player.all_player_img = load_all_player_image(game, error);
	if (*error < 0)
		destroy_game_boom_explosion_all_clear(game, *error);
	game->player.img = game->player.all_player_img[IDLE][FRONT][0];
	game->all_monster_img = load_all_monster_img(game, error);
	if (*error < 0)
		destroy_game_boom_explosion_all_clear(game, *error);
	game->monster = set_all_monster(game, game->map.map,
			game->map.count_monster, error);
	if (*error < 0)
		destroy_game_boom_explosion_all_clear(game, *error);
}

int	ft_game(t_map *map)
{
	t_game		game;
	int			error;

	game.map = *map;
	init_game_variable(&game);
	error = 0;
	game.vars.mlx = mlx_init();
	if (!game.vars.mlx)
		mlx_crash(map);
	game.vars.window = mlx_new_window(game.vars.mlx, game.map.nb_columns
			* IMG_SIZE, game.map.nb_lines * IMG_SIZE, "so_long");
	if (!game.vars.window)
		window_crash(&game, map);
	init_game_image(&game, game.map.nb_columns * IMG_SIZE, game.map.nb_lines
		* IMG_SIZE, &game.map_image);
	ft_init_game(&game, &error);
	mlx_do_key_autorepeatoff(game.vars.mlx);
	render_map(&game);
	set_player_postion(&game.map, &game.player);
	mlx_put_image_to_window(game.vars.mlx, game.vars.window,
		game.map_image.img, 0, 0);
	call_hook(&game);
	return (0);
}
