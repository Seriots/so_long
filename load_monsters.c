/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_monsters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:07:03 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 21:41:33 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>

char	*get_path_img_monster(int direction, int i, int *error)
{
	const char	*directions[] = {"back/", "front/", "left/", "right/"};
	const char	*values[] = {"1.xpm", "2.xpm", "3.xpm"};
	char		*path;
	size_t		length;

	length = ft_strlen("assets_xpm/monster/walk/")
		+ ft_strlen(directions[direction]) + ft_strlen(values[i]);
	path = ft_calloc(sizeof(char), length + 1);
	if (!path)
	{
		*error = -3;
		return (0);
	}
	ft_strlcat(path, "assets_xpm/monster/walk/", length + 1);
	ft_strlcat(path, directions[direction], length + 1);
	ft_strlcat(path, values[i], length + 1);
	return (path);
}

void	check_monster_anim_error(int *error, t_data *all_img)
{
	if (*error < 0)
	{
		free(all_img);
		*error = -3;
	}
}

t_data	*load_anim_monster(t_game *game, int *error, int direction)
{
	t_data	*all_img;
	int		i;
	char	*path;

	all_img = malloc(sizeof(t_data) * NB_ANIM_MONSTER_IMG);
	if (!all_img)
		set_error_image(error);
	i = -1;
	while (++i < NB_ANIM_MONSTER_IMG)
	{
		path = get_path_img_monster(direction, i, error);
		if (!path)
		{
			free(all_img);
			*error = -3;
			return (0);
		}
		all_img[i] = load_img(game, path, error);
		check_monster_anim_error(error, all_img);
		if (*error < 0)
			return (0);
	}
	return (all_img);
}

t_data	**load_all_monster_img(t_game *game, int *error)
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
		all_img[i] = load_anim_monster(game, error, i);
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
