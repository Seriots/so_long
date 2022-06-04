/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 01:28:56 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 19:30:29 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "mlx_linux/mlx.h"
#include "libft/libft.h"

t_data	get_image(t_game *game, char c)
{
	if (c == '1')
		return (game->all_image[WALL]);
	else if (c == '2')
		return (game->all_image[WALL_TOP]);
	else if (c == '3')
		return (game->all_image[WALL_BOTTOM]);
	else if (c == '4')
		return (game->all_image[WALL_LEFT]);
	else if (c == '5')
		return (game->all_image[WALL_RIGHT]);
	else if (c == '6')
		return (game->all_image[WALL_CORNER_TL]);
	else if (c == '7')
		return (game->all_image[WALL_CORNER_TR]);
	else if (c == '8')
		return (game->all_image[WALL_CORNER_BL]);
	else if (c == '9')
		return (game->all_image[WALL_CORNER_BR]);
	else if (c == 'E')
		return (game->all_image[EXIT]);
	else if (c == 'C')
		return (game->all_image[ITEM]);
	else
		return (game->all_image[GROUND]);
}

unsigned int	get_pxl_color(t_data img, int x, int y)
{
	char	*dst;

	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int	set_image(t_data *map_img, t_data img, int x, int y)
{
	char	*dst;
	int		i;
	int		j;

	j = 0;
	while (j < IMG_SIZE)
	{
		i = 0;
		while (i < IMG_SIZE)
		{
			dst = map_img->addr + ((y * IMG_SIZE + j) * map_img->line_length
					+ (x * IMG_SIZE + i) * (map_img->bits_per_pixel / 8));
			*(unsigned int *)dst = get_pxl_color(img, i, j);
			i ++;
		}
		j ++;
	}
	return (0);
}

int	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.nb_lines)
	{
		x = 0;
		while (x < game->map.nb_columns)
		{
			set_image(&game->map_image, get_image(game, game->map.map[y][x]),
				x, y);
			x ++;
		}
		y ++;
	}
	return (0);
}
