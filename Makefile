NAME = cub3D

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

MLX_PATH = minilibx-linux/

MLX_NAME = libmlx_Linux.a

MLX = $(MLX_PATH)$(MLX_NAME)

LIBFT_PATH = libft/

LIBFT_NAME = libft.a

LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)

SRCS = map_parcing/check_map.c \
		image_render.c \
		map_parcing/read_file.c \
		map_parcing/parce_color.c \
		main.c \
		clean_exit.c \
		utils.c \
		map_utils.c \
		texture_utils.c \
		draw_map.c \
		draw_map_inits.c \
		hooks.c \
		player_movements.c

SRCS_BONUS = bonus/map_parcing/check_map_bonus.c \
			bonus/image_render_bonus.c \
			bonus/map_parcing/read_file_bonus.c \
			bonus/map_parcing/parce_color_bonus.c \
			bonus/map_parcing/parcing_utils_bonus.c \
			bonus/map_parcing/set_map_items_bonus.c \
			bonus/main_bonus.c \
			bonus/clean_exit_bonus.c \
			bonus/utils_bonus.c \
			bonus/texture_utils_bonus.c \
			bonus/draw_map_bonus.c \
			bonus/hooks_bonus.c \
			bonus/player_movements_bonus.c \
			bonus/minimap_bonus.c \
			bonus/minimap_2_bonus.c \
			bonus/door_utils_bonus.c \
			bonus/door_render_bonus.c \
			bonus/sprites_bonus.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

INCL = -I/usr/include/ \
		-I/usr/include/X11 \
		-Iminilibx-linux/ \
		-Ilibft/

all:	$(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS) cub3d.h
	@rm -f .bonus
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME) $(MLX) $(INCL) $(LIBFT) -L/usr/lib -lXext -lX11 -lm -lz

$(LIBFT):
	@make -sC $(LIBFT_PATH)

$(MLX):
	@make -sC $(MLX_PATH)

%.o: %.c Makefile cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INCL)

bonus: .bonus

.bonus: $(LIBFT) $(MLX) $(OBJS_BONUS) bonus/cub3d_bonus.h
	$(CC) $(OBJS_BONUS) $(CFLAGS) -o $(NAME) $(MLX) $(LIBFT) $(INCL) -L/usr/lib -lXext -lX11 -lm -lz
	@touch .bonus
	rm -f $(OBJS)

norm:
	norminette $(SRCS) $(SRCS_BONUS) libft/

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	@make clean -C $(MLX_PATH)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)
	@rm -f .bonus
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re bonus
