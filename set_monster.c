/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_monster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:08:46 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 19:54:59 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "libft/libft.h"
#include <stdlib.h>

t_monster	set_one_monster(t_game *game, char c, float x, float y)
{
	t_monster	monster;

	monster.x = x * IMG_SIZE;
	monster.y = y * IMG_SIZE;
	if (c == 'W')
		monster.direction = LEFT;
	else if (c == 'Y')
		monster.direction = RIGHT;
	else if (c == 'X')
		monster.direction = FRONT;
	else
		monster.direction = BACK;
	if (c == 'Y' || c == 'X')
		monster.movement = MONSTER_SPEED * (game->map.nb_columns
				* game->map.nb_lines);
	else
		monster.movement = -MONSTER_SPEED * (game->map.nb_columns
				* game->map.nb_lines);
	monster.current_img = 0;
	monster.img = game->all_monster_img[monster.direction][0];
	monster.sleep = MONSTER_ANIM_TX / (game->map.nb_columns
			* game->map.nb_lines);
	return (monster);
}

void	iter_all_monster(t_game *game, char **map,
			const char *set, t_monster *all_monster)
{
	float		x;
	float		y;
	int			i;

	i = 0;
	y = 0;
	while (map[(int)y])
	{
		x = 0;
		while (map[(int)y][(int)x])
		{
			if (check_case(map[(int)y][(int)x], (char *)set))
			{
				all_monster[i] = set_one_monster(game,
						map[(int)y][(int)x], x, y);
				i ++;
			}
			x ++;
		}
		y ++;
	}
}

t_monster	*set_all_monster(t_game	*game, char **map,
				int nb_monster, int *error)
{
	t_monster	*all_monster;
	const char	*set = "WXYZ";

	all_monster = malloc(sizeof(t_monster) * (nb_monster));
	if (!all_monster)
	{
		*error = -3;
		return (0);
	}
	iter_all_monster(game, map, set, all_monster);
	return (all_monster);
}
