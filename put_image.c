/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:19:39 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 19:19:53 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "mlx_linux/mlx.h"
#include <math.h>

int	put_object(t_data *map_img, t_data img, float x_object, float y_object)
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
			dst = map_img->addr + ((((int)floor(y_object) + y))
					* map_img->line_length + (((int)floor(x_object)
							+ x)) * (map_img->bits_per_pixel / 8));
			color = get_pxl_color(img, x, y);
			if (color != 4278190080)
				*(unsigned int *)dst = color;
			x++;
		}
		y ++;
	}
	return (0);
}

int	put_number(t_data *map_img, t_data img, float x_object, float y_object)
{
	char			*dst;
	unsigned int	color;
	int				x;
	int				y;

	y = 0;
	while (y < 12)
	{
		x = 0;
		while (x < 12)
		{
			dst = map_img->addr + ((((int)floor(y_object) + y))
					* map_img->line_length + (((int)floor(x_object)
							+ x)) * (map_img->bits_per_pixel / 8));
			color = get_pxl_color(img, x, y);
			if (color != 4278190080)
				*(unsigned int *)dst = color;
			x++;
		}
		y ++;
	}
	return (0);
}

int	print_count_image(t_data *map_img, t_data img, int x, int y)
{
	char			*dst;
	unsigned int	color;
	int				i;
	int				j;

	j = 0;
	while (j < 12)
	{
		i = 0;
		while (i < 12)
		{
			dst = map_img->addr + ((j + y) * map_img->line_length
					+ (i + x) * (map_img->bits_per_pixel / 8));
			color = get_pxl_color(img, i, j);
			if (color != 4278190080)
				*(unsigned int *)dst = color;
			i++;
		}
		j ++;
	}
	return (0);
}

t_data	change_img(int	*current_img, t_data *lst_img, int max_anim)
{
	if (*current_img >= max_anim)
		*current_img = 0;
	else
		*current_img += 1;
	return (lst_img[*current_img]);
}
