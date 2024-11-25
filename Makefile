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
		map_parcing/parcing_utils.c \
		map_parcing/set_map_items.c \
		main.c \
		clean_exit.c \
		utils.c \
		texture_utils.c \
		draw_map.c \
		hooks.c \
		player_movements.c \
		minimap.c \
		minimap_2.c \
		door_utils.c

OBJS = $(SRCS:.c=.o)

INCL = -I/usr/include/ \
		-I/usr/include/X11 \
		-Iminilibx-linux/ \
		-Ilibft/

all:	$(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS) cub3d.h
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME) $(MLX) $(INCL) $(LIBFT) -L/usr/lib -lXext -lX11 -lm -lz

$(LIBFT):
	@make -sC $(LIBFT_PATH)

$(MLX):
	@make -sC $(MLX_PATH)

%.o: %.c Makefile cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INCL)

clean:
	rm -f $(OBJS)
	@make clean -C $(MLX_PATH)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re
