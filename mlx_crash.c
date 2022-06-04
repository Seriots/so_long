/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_crash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:15:10 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 21:32:24 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "libft/libft.h"
#include "mlx_linux/mlx.h"
#include "include/parsing.h"

void	mlx_crash(t_map *map)
{
	ft_free_map(map->map);
	ft_printf("Error\n-Mlx crash\n");
	exit(0);
}

void	window_crash(t_game *game, t_map *map)
{
	mlx_destroy_display(game->vars.mlx);
	free(game->vars.mlx);
	mlx_crash(map);
}
