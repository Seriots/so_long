/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:27:06 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/25 16:00:54 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"
#include "include/parsing.h"

int	main(int argc, char *argv[])
{
	t_map	map;
	int		error;

	error = 0;
	map = ft_parsing_map(argc, argv, &error);
	if (map.map == 0)
		return (ft_print_error(error));
	if (error < 0)
	{
		ft_free_map(map.map);
		return (ft_print_error(error));
	}
	ft_print_error(ft_game(&map));
}
