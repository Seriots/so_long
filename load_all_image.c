/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_all_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:27:21 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 21:41:01 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>

t_data	*free_all_image(t_data *all_image)
{
	free(all_image);
	return (0);
}

t_data	*set_error_image(int *error)
{
	*error = -3;
	return (0);
}

t_data	*load_all_image(t_game *game, int *error)
{
	t_data		*all_image;
	const char	*path[] = {
		"assets_xpm/field_tiles/exit.xpm",
		"assets_xpm/field_tiles/wall.xpm",
		"assets_xpm/field_tiles/wallTop.xpm",
		"assets_xpm/field_tiles/wallBottom.xpm",
		"assets_xpm/field_tiles/wallLeft.xpm",
		"assets_xpm/field_tiles/wallRight.xpm",
		"assets_xpm/field_tiles/wallCornerTopLeft.xpm",
		"assets_xpm/field_tiles/wallCornerTopRight.xpm",
		"assets_xpm/field_tiles/wallCornerBottomLeft.xpm",
		"assets_xpm/field_tiles/wallCornerBottomRight.xpm",
		"assets_xpm/items/item.xpm",
		"assets_xpm/field_tiles/ground.xpm",
		"assets_xpm/field_tiles/ground2.xpm"};

	all_image = malloc(sizeof(t_data) * NB_MAP_IMAGE);
	if (!all_image)
		return (set_error_image(error));
	*error = set_map_image(&all_image, game, path, NB_MAP_IMAGE);
	if (*error < 0)
		return (free_all_image(all_image));
	return (all_image);
}

t_data	*load_all_number(t_game *game, int *error)
{
	t_data		*all_image;
	const char	*path[] = {
		"assets_xpm/items/zero.xpm",
		"assets_xpm/items/one.xpm",
		"assets_xpm/items/two.xpm",
		"assets_xpm/items/three.xpm",
		"assets_xpm/items/four.xpm",
		"assets_xpm/items/five.xpm",
		"assets_xpm/items/six.xpm",
		"assets_xpm/items/seven.xpm",
		"assets_xpm/items/eight.xpm",
		"assets_xpm/items/nine.xpm"};

	all_image = malloc(sizeof(t_data) * 10);
	if (!all_image)
		return (set_error_image(error));
	*error = set_map_image(&all_image, game, path, 10);
	if (*error < 0)
		return (free_all_image(all_image));
	return (all_image);
}
