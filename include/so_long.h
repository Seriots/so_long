/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:55:51 by lgiband           #+#    #+#             */
/*   Updated: 2022/05/31 15:32:19 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define IMG_SIZE 32

# define STRING_UPDATE 2

# define NB_MAP_IMAGE 13

# ifdef VAL
#  define SPEED 0.0002f
#  define MONSTER_SPEED 0.0001f
#  define IDLE_ANIM_TX 10000
#  define WALK_ANIM_TX 6000
#  define DIE_ANIM_TX 5000
#  define MONSTER_ANIM_TX 12000
# else
#  define SPEED 0.0002f
#  define MONSTER_SPEED 0.0001f
#  define IDLE_ANIM_TX 100000
#  define WALK_ANIM_TX 60000
#  define DIE_ANIM_TX 40000
#  define MONSTER_ANIM_TX 80000
# endif

# define COLL_BOX 24

# define EXIT 0
# define WALL 1
# define WALL_TOP 2
# define WALL_BOTTOM 3
# define WALL_LEFT 4
# define WALL_RIGHT 5
# define WALL_CORNER_TL 6
# define WALL_CORNER_TR 7
# define WALL_CORNER_BL 8
# define WALL_CORNER_BR 9
# define ITEM 10
# define GROUND 11
# define GROUND2 12

# define IDLE 0
# define WALK 1
# define DIE 2

# define BACK 0
# define FRONT 1
# define LEFT 2
# define RIGHT 3

# define NB_ANIM_PLAYER_IMG 4
# define NB_ANIM_MONSTER_IMG 3

typedef struct s_vars {
	void	*mlx;
	void	*window;
}	t_vars;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_data;

typedef struct s_update {
	t_data		img;
	int			x;
	int			y;
}				t_update;

typedef struct s_map {
	char	**map;
	int		player;
	int		items;
	int		exit;
	int		exit_x;
	int		exit_y;
	int		count_monster;
	int		nb_lines;
	int		nb_columns;
}			t_map;

typedef struct s_monster {
	t_data		img;
	float		x;
	float		y;
	int			current_img;
	int			direction;
	float		movement;
	int			next_case_x;
	int			next_case_y;
	int			sleep;
}				t_monster;

typedef struct s_player {
	t_data	img;
	t_data	***all_player_img;
	int		state;
	int		direction;
	int		current_img;
	float	x;
	float	y;
	int		move_top;
	int		move_bot;
	int		move_left;
	int		move_right;
	int		nb_move;
	int		nb_items;
	int		previous_x;
	int		previous_y;
	int		sleep;
	float	speed;
}			t_player;

typedef struct s_game {
	t_player	player;
	t_monster	*monster;
	t_data		**all_monster_img;
	t_map		map;
	t_vars		vars;
	t_data		map_image;
	t_data		*all_image;
	t_data		*all_number;
	t_update	count_image;
	int			end;
	int			die;
	char		*allowed_case;
}				t_game;

/*main.c*/
void			init_game_image(t_game *game, int width, int height,
					t_data *img);
int				ft_game(t_map *map);

/*mlx_crash.c*/
void			window_crash(t_game *game, t_map *map);
void			mlx_crash(t_map *map);

/*event.c*/
int				key_pressed(int keycode, t_game *game);
int				close_request(t_game *game);
int				key_released(int keycode, t_game *game);

/*render_map.c*/
t_data			get_image(t_game *game, char c);
unsigned int	get_pxl_color(t_data img, int x, int y);
int				set_image(t_data *map_img, t_data img, int x, int y);
int				render_map(t_game *game);

/*render_player.c*/
int				render_player(t_player *player);

/*display.c*/
int				display(t_game *game);
void			update_monster(t_game *game, int i);

/*load_all_image.c*/
t_data			*set_error_image(int *error);
t_data			load_img(t_game *game, char *path, int *error);
void			set_player_postion(t_map *map, t_player *player);
t_data			*load_all_image(t_game *game, int *error);
t_data			***load_all_player_image(t_game *game, int *error);
t_data			**load_all_monster_img(t_game *game, int *error);
t_data			*load_all_number(t_game *game, int *error);

/*set_map_image.c*/
int				set_map_image(t_data **all_image, t_game *game,
					const char **path, int count);
void			set_player_postion(t_map *map, t_player *player);
void			set_player_variable(t_player *player, t_map *map,
					int x, int y);

/*leak_cleaner.c*/
int				destroy_game_boom_explosion_all_clear(t_game *game, int error);

/*update.c*/
int				check_collision_monster(t_game *game);
void			set_count_image(t_game *game, char *count);
void			redraw_player_case(t_game *game);
int				update_map(t_game *game);

/*redraw.c*/
void			redraw_player_case(t_game *game);
void			redraw_monsters_case(t_game *game);

/*put_image.c*/
t_data			change_img(int	*current_img, t_data *lst_img, int max_anim);
int				print_count_image(t_data *map_img, t_data img, int x, int y);
int				put_number(t_data *map_img, t_data img,
					float x_object, float y_object);
int				put_object(t_data *map_img, t_data img,
					float x_object, float y_object);

/*check_update.c*/
int				check_case(char c, char *set);
int				check_ground(float x, float y, char **map, char *allowed_case);
void			check_move_player(t_player *player, char **map,
					char *allowed_case);
int				check_ground_monster_x(float x, float y,
					char **map, char *allowed_case);
int				check_ground_monster_y(float x, float y,
					char **map, char *allowed_case);

/*check_map.c*/
void			check_items(t_player *player, t_map *map);
void			check_exit(t_player *player, t_map *map, t_game *game);
int				check_movement(t_player *player);

/*set_monster.c*/
t_monster		*set_all_monster(t_game	*game, char **map,
					int nb_monster, int *error);
#endif
