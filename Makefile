NAME = cub3D

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

MLX_PATH = minilibx-linux/

MLX_NAME = libmlx_Linux.a

MLX = $(MLX_PATH)$(MLX_NAME)

LIBFT_PATH = libft/

LIBFT_NAME = libft.a

LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)

SRCS = calculations_for_x.c \
		image_render.c \
		inits.c \
		main.c \
		parce_map.c \
		utils.c

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

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCL)

clean:
	rm -f $(OBJS)
	@make clean -C $(MLX_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
