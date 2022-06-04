/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 00:53:25 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/24 17:21:42 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "so_long.h"

/*parsing.c*/
t_map	ft_parsing_map(int argc, char *argv[], int *error);

/*parsing_utils.c*/
int		ft_print_error(int code);
char	**ft_free_map(char **map);
t_map	set_error(int *error, int code, t_map map);
int		ft_count_lines(int fd);
void	set_map_struct(t_map *map);

int		ft_check_map_params(t_map *map, int *error);
void	set_exit(t_map *map, int x, int y);
int		check_end(char *argv);

/*set_wall.c*/
void	set_wall(t_map *map);
#endif