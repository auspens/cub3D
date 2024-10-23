/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:09:47 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/23 16:23:12 by auspensk         ###   ########.fr       */
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
	WEST,
	CEILING,
	FLOOR
}	t_sides;

typedef struct coords {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_coords;

typedef struct img_data {
	void	*mlx_img;
	char	*img_addr;
	int		bpp;
	int		img_line_len;
	int		img_endian;
}	t_img_data;

typedef struct data {
	void		*mlx;
	void		*mlx_win;
	t_img_data	*img;
}	t_data;

typedef struct data_x{
	double	cam_x;
	double	ray_x;
	double	ray_y;
	double	del_dist_x;
	double	del_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		map_x;
	int		map_y;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	t_sides	side;
}	t_data_x;

int			**parce_map(void);
t_data		*init_data(void);
t_img_data	*new_img(t_data *data);
void		my_pixel_put(t_img_data *data, int x, int y, int color);
int			get_color(t_sides side);
int			render_loop(t_data *data, t_coords *coords, int **map);

/*calculations for x*/
void		calc_step_and_side_dist(t_coords *coords, t_data_x *data_x);
void		calc_perp_wall_dist(t_data_x *data_x);
void		calc_data_x(t_coords *coords, t_data_x *data_x, int x);
void		calc_line_height(t_data_x *data_x);

#endif
