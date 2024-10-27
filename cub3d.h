/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:09:47 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/27 16:18:56 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx-linux/mlx.h"
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/Xos.h>
# include <X11/Xatom.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <float.h>

# ifndef SCRNWIDTH
#  define SCRNWIDTH 640
# endif
# ifndef SCRNHEIGHT
#  define SCRNHEIGHT 480
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
	int			hit;
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
}	t_img_data;

typedef struct s_tx
{
	t_img_data		*n;
	t_img_data		*s;
	t_img_data		*e;
	t_img_data		*w;
}		t_tx;

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
}	t_data;


/*read_file*/
int			open_mapfile(char *path);
void		get_map(t_data *data, char *line, int fd, int size);
void		get_input(t_data *data, int fd, int size);

/*clean_exit*/
void		clean_exit(int code, char *msg, t_data *data);
void		free_data(t_data *data);
void		free_map(char **map);

/*check_map*/
int			check_valid_map(t_data *data);
int			check_other_lines(t_data *data, int width, int height);
int			check_last_line(t_data *data, int num, int width);
int			check_char(t_data *data, char *line, int idx, int lnum, int width);

/*draw map*/
void		draw_frame(t_data *md);

/*map_utils*/
void		map_error(int fd, t_data *data, char *line, int error);

/*image_render*/
void		draw_line_to_img(t_data *data, t_sides side, int x, int height);

/*utils*/
int			gen_trgb(int opacity, int red, int green, int blue);
void		my_pixel_put(t_img_data *data, int x, int y, int color);
t_img_data	*new_img(t_data *data);
t_data		*init_data(void);

/*texture_utils*/
int			get_txt_color(t_img_data img, t_sides side, int x, int y);
t_img_data	*get_texture(char *addr, t_data *data);

#endif
