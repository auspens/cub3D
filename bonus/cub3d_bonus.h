/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:09:47 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/29 13:02:24 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <float.h>
# include <limits.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/Xos.h>
# include <X11/Xatom.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <sys/time.h>
# include <float.h>

# ifndef SCRNWIDTH
#  define SCRNWIDTH 1024
# endif
# ifndef SCRNHEIGHT
#  define SCRNHEIGHT 776
# endif
# define PI 3.14159265359

typedef enum sides{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_sides;

typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_dda
{
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_x;
	double		delta_y;
	int			step_x;
	int			step_y;
	t_sides		side;
	char		hit;
}	t_dda;

typedef struct s_ray
{
	t_coord	dir;
	t_coord	origin;
}	t_ray;

typedef struct img_data {
	void	*mlx_img;
	char	*img_addr;
	int		bpp;
	int		img_line_len;
	int		img_endian;
	int		width;
	int		height;
	int		scale;
}	t_img_data;

typedef struct s_tx
{
	t_img_data		*n;
	t_img_data		*s;
	t_img_data		*e;
	t_img_data		*w;
}		t_tx;

typedef struct draw_data {
	int			line_height;
	double		wall_x;
	int			txtr_x;
	int			txtr_y;
	double		per_wall_dist;
	t_img_data	*txtr;
	double		step;
	double		txtr_pos;
}	t_draw_data;

typedef struct s_sprite
{
  t_coord pos;
  t_img_data *t;
  int size;
  int moves;
  int scale;
}	t_sprite;

typedef struct s_door {
	int	x;
	int	y;
	int	state;
	double	open_ratio;
	t_img_data		*txtr;
	time_t	tm_stamp;
	t_sprite	sprite;
}	t_door;

typedef struct m_map_colors
{
	int	s;
	int	d;
	int	w;
	int	p;
}	t_m_map_colors;

typedef struct data {
	void		*mlx;
	void		*mlx_win;
	t_img_data	*img;
	t_tx		*txt;
	int			color_ceiling;
	int			color_floor;
	t_coord		player;
	t_coord		dir;
	t_coord		plane;
	char		**map;
	struct timeval	oldtime;
	double		elapsed;
	size_t		frames;
	double 		buffer[SCRNWIDTH];
	t_door		doors[24];
	int			num_drs;
	t_door		*can_open;
	t_sprite	*sprite;
	int			redraw;
	t_img_data	m_map;
	t_m_map_colors	m_map_colors;
}	t_data;


/*read_file*/
int			open_mapfile(char *path);
void		get_map(t_data *data, char *line, int fd, int size);
void		get_input(t_data *data, int fd, int size);

/*clean_exit*/
void		clean_exit(int code, char *msg, t_data *data);
void		free_data(t_data *data);
void		free_array(char **array);

/*check_map*/
void		check_valid_map(t_data *data);
void		set_direction(t_data *data, char c);

/*set_map_items*/
void		set_player(t_data *data, int x, int y);
void		set_door(t_data *data, int x, int y);

/*parcing_utils.c*/
void		trim_newlines(t_data *data);
int			char_ind(char *str, char c);
void		newmap_error(int fd, t_data *data, char *line);

/*draw map*/
void		draw_frame(t_data *md);
void		perform_dda(t_dda *dda, char **map);
void		handle_sprite(t_data *data);

/*image_render*/
void		draw_line_to_img(t_data *data, int x, t_draw_data *draw, int y);
void		calc_wall_txtr_x(t_dda dda, t_draw_data *draw, t_data *data, t_ray ray);
unsigned int	my_pixel_get(t_img_data *img, int x, int y);
void		calc_line_height(t_dda dda, t_draw_data *draw_data);

/*utils*/
int			gen_trgb(int opacity, int red, int green, int blue);
unsigned int	my_pixel_get(t_img_data *img, int x, int y);
void		my_pixel_put(t_img_data *data, int x, int y, int color);
t_img_data	*new_img(t_data *data);
t_data		*init_data(void);
t_coord		rotate_vector(t_coord src, double angle);

/*texture_utils*/
int			get_texture(char *addr, t_data *data, t_img_data **img_data);

/*hooks*/
void		set_hooks(t_data *data);

/*player_movements*/
void		move_player(t_data *data, int key);
void		rotate_player(t_data *data, int key);

/*parce_color*/
int			parce_color(t_data *data, char **lines, int fd);

/*minimap*/
void		init_minimap(t_data *data);
void		draw_minimap(t_data *data);

/*minimap_2*/
void		check_char_and_draw(t_coord coord, t_data *data, char *nl, char value);

/*door_utils*/
void		iter_doors(t_data *data);

/*door_render*/
void		handle_door(t_dda dda, t_draw_data *draw, t_data *data, t_ray ray);

#endif
