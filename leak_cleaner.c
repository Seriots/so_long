/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:58:25 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 17:59:36 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "include/parsing.h"
#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>

void	free_state_player_img(t_game *game, t_data ***all_img, int x, int y)
{
	int	z;

	while (y < 4)
	{
		z = 0;
		if (all_img[x][y])
		{
			while (z < NB_ANIM_PLAYER_IMG)
			{
				mlx_destroy_image(game->vars.mlx, all_img[x][y][z].img);
				z++;
			}
			free(all_img[x][y]);
		}
		y ++;
	}
	free(all_img[x]);
}

void	free_all_player_img(t_game *game, t_data ***all_img)
{
	int	x;
	int	y;

	x = 0;
	if (all_img)
	{
		while (x < 3)
		{
			y = 0;
			if (all_img[x])
				free_state_player_img(game, all_img, x, y);
			x ++;
		}
		free(all_img);
	}
}

void	free_all_monster_img(t_game *game, t_data **all_img)
{
	int	y;
	int	z;

	y = 0;
	if (all_img)
	{
		while (y < 4)
		{
			z = 0;
			if (all_img[y])
			{
				while (z < NB_ANIM_MONSTER_IMG)
				{
					mlx_destroy_image(game->vars.mlx, all_img[y][z].img);
					z++;
				}
				free(all_img[y]);
			}
			y ++;
		}
		free(all_img);
	}
}

void	destroy_list(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->map.nb_lines)
		free(game->map.map[i]);
	free(game->map.map);
	i = -1;
	if (game->all_image)
	{
		while (++i < NB_MAP_IMAGE)
			mlx_destroy_image(game->vars.mlx, game->all_image[i].img);
		free(game->all_image);
	}
	i = -1;
	if (game->all_number)
	{
		while (++i < 10)
			mlx_destroy_image(game->vars.mlx, game->all_number[i].img);
		free(game->all_number);
	}
}

int	destroy_game_boom_explosion_all_clear(t_game *game, int error)
{
	mlx_do_key_autorepeaton(game->vars.mlx);
	destroy_list(game);
	mlx_destroy_window(game->vars.mlx, game->vars.window);
	free_all_monster_img(game, game->all_monster_img);
	free(game->monster);
	free_all_player_img(game, game->player.all_player_img);
	mlx_destroy_image(game->vars.mlx, game->map_image.img);
	mlx_loop_end(game->vars.mlx);
	mlx_destroy_display(game->vars.mlx);
	free(game->vars.mlx);
	ft_print_error(error);
	exit(0);
}
