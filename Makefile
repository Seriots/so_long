
MLX = mlx_linux/libmlx.a

LIBFT = libft/libft.a

SRCS = main.c game.c parsing.c parsing_utils.c  set_wall.c display.c display2.c load_all_image.c leak_cleaner.c render_map.c event.c update.c update_check.c update_check2.c check_map.c parsing_utils2.c load_monsters.c load_all_player_img.c set_monster.c redraw.c put_image.c mlx_crash.c set_all_image.c

TEST = test.c

OBJS_DIR = objs/

OBJS = $(patsubst %.c,objs/%.o,$(SRCS))

CC = cc

FLAGS = -Wall -Werror -Wextra -O3

INC = include \

NAME = so_long

objs/%.o: %.c include/so_long.h $(LIBFT)
	$(CC) $(FLAGS) $(VAL) -I$(INC) -Imlx_linux -c $< -o $@

all : $(NAME)

$(MLX) :
	make -C $(dir $(MLX))

$(LIBFT) :
	make -C $(dir $(LIBFT))

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(VAL) libft/libft.a -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

val: VAL = -D VAL
val: $(NAME)

debug : $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) -g3 -fsanitize=address $(OBJS) libft.a -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean :
	rm -f $(OBJS)
	make -C $(dir $(LIBFT)) fclean

fclean :
	rm -f $(NAME)
	make clean

re :
	make fclean
	make all

.PHONY : re fclean clean all debug