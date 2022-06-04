/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_all_player_img.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:09:44 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 21:42:39 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>

char	*get_path_img_player(int state, int direction, int i, int *error)
{
	const char	*states[] = {"idle/", "walk/", "die/"};
	const char	*directions[] = {"back/", "front/", "left/", "right/"};
	const char	*values[] = {"1.xpm", "2.xpm", "3.xpm", "4.xpm"};
	char		*path;
	size_t		length;

	length = ft_strlen("assets_xpm/player/") + ft_strlen(states[state])
		+ ft_strlen(directions[direction]) + ft_strlen(values[i]);
	path = ft_calloc(sizeof(char), length + 1);
	if (!path)
	{
		*error = -3;
		return (0);
	}
	ft_strlcat(path, "assets_xpm/player/", length + 1);
	ft_strlcat(path, states[state], length + 1);
	ft_strlcat(path, directions[direction], length + 1);
	ft_strlcat(path, values[i], length + 1);
	return (path);
}

t_data	load_img(t_game *game, char *path, int *error)
{
	t_data		img;

	img.img = mlx_xpm_file_to_image(game->vars.mlx, path,
			&img.width, &img.height);
	if (!img.img)
		*error = -3;
	else
	{
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
		if (!img.addr)
		{
			*error = -3;
			mlx_destroy_image(game->vars.mlx, img.img);
		}
	}
	free(path);
	return (img);
}

t_data	*load_anim_player(t_game *game, int *error, int state, int direction)
{
	t_data	*all_img;
	char	*path;
	int		i;

	all_img = malloc(sizeof(t_data) * NB_ANIM_PLAYER_IMG);
	if (!all_img)
		set_error_image(error);
	i = 0;
	while (i < NB_ANIM_PLAYER_IMG)
	{
		path = get_path_img_player(state, direction, i, error);
		if (!path)
		{
			free(all_img);
			set_error_image(error);
		}
		all_img[i] = load_img(game, path, error);
		if (*error < 0)
		{
			free(all_img);
			set_error_image(error);
		}
		i++;
	}
	return (all_img);
}

t_data	**load_state_player(t_game *game, int *error, int state)
{
	t_data	**all_img;
	int		i;

	all_img = malloc(sizeof(t_data *) * 4);
	if (!all_img)
	{
		*error = -3;
		return (0);
	}
	i = 0;
	while (i < 4)
	{
		all_img[i] = load_anim_player(game, error, state, i);
		if (!all_img[i])
		{
			free(all_img);
			*error = -3;
			return (0);
		}
		i++;
	}
	return (all_img);
}

t_data	***load_all_player_image(t_game *game, int *error)
{
	t_data	***all_img;
	int		i;

	all_img = malloc(sizeof(t_data **) * 3);
	if (!all_img)
	{
		*error = -3;
		return (0);
	}
	i = 0;
	while (i < 3)
	{
		all_img[i] = load_state_player(game, error, i);
		if (!all_img[i])
		{
			free(all_img);
			*error = -3;
			return (0);
		}
		i++;
	}
	return (all_img);
}
