/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleonora <eleonora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:09:47 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/09 11:49:30 by eleonora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx-linux/mlx.h"
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <float.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/Xos.h>
# include <X11/Xatom.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <sys/time.h>


# ifndef SCRNWIDTH
#  define SCRNWIDTH 1024
# endif
# ifndef SCRNHEIGHT
#  define SCRNHEIGHT 800
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
}	t_img_data;

typedef struct s_tx
{
	t_img_data		*n;
	t_img_data		*s;
	t_img_data		*e;
	t_img_data		*w;
	t_img_data		*dr;
}		t_tx;

typedef struct draw_data {
	int			line_height;
	double		wall_x;
	int		txtr_x;
	int		txtr_y;
	double		per_wall_dist;
	t_img_data	*txtr;
	double		step;
	double		txtr_pos;
}	t_draw_data;

typedef struct s_door {
	int	x;
	int y;
	int state;
	double	open_ratio;
}	t_door;

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
	t_door	door;
	int can_open[2];
	int redraw;
}	t_data;



/*read_file*/
int			open_mapfile(char *path);
void		get_map(t_data *data, char *line, int fd, int size);
void		get_input(t_data *data, int fd, int size);

/*clean_exit*/
void		clean_exit(int code, char *msg, t_data *data);
void		free_data(t_data *data);
void		free_array(char **array);
void		exit_at_reading_input(t_data *data, int fd, char **arr, char *msg);


/*check_map*/
void		check_valid_map(t_data *data);

/*draw map*/
void		draw_frame(t_data *md);
void	calc_line_height(t_dda dda, t_draw_data *draw_data);
void	perform_dda(t_dda *dda, char **map);



/*map_utils*/
void		map_error(int fd, t_data *data, char *line, int error);

/*image_render*/
void		draw_line_to_img(t_data *data, int x, t_draw_data *draw);
void		calc_wall_txtr_x(t_dda dda, t_draw_data *draw, t_data *data, t_ray ray);

/*utils*/
int			gen_trgb(int opacity, int red, int green, int blue);
void		my_pixel_put(t_img_data *data, int x, int y, int color);
t_img_data	*new_img(t_data *data);
t_data		*init_data(void);
t_coord		rotate_vector(t_coord src, double angle);

/*texture_utils*/
int			get_txt_color(t_img_data img, t_sides side, int x, int y);
int			get_texture(char *addr, t_data *data, t_img_data **img_data);

/*hooks*/
void		set_hooks(t_data *data);

/*parce_color*/
int			parce_color(t_data *data, char **lines, int fd);

#endif
