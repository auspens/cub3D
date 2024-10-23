/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:51:01 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/23 16:23:52 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rotate_vector(int x, int y, int angle, char c)
{
	int	y_r;
	int	x_r;

	x_r = x * cos(angle) - y * sin(angle);
	y_r = x * sin(angle) + y * cos(angle);
	if (c == 'x')
		return (x_r);
	else
		return (y_r);
}

void	plane_init(t_coords *coord)
{
	double	fov;
	double	fov_rad;
	double	scale;

	fov = 90;
	fov_rad = (fov * PI) / 180;
	scale = tan(fov_rad / 2);
	coord->plane_x = rotate_vector(coord->dir_x, coord->dir_y, -PI / 2, 'x')
		* scale;
	coord->plane_y = rotate_vector(coord->dir_x, coord->dir_y, -PI / 2, 'y')
		* scale;
}
/*for camera plane with 90 degrees fov no additional scaling is required,
we can just rotate the direction vector.
To change the fov, the function plane_init can be used
to scale the camera plane*/

void	init_coords(t_coords *coord)
{
	coord->pos_x = 20;
	coord->pos_y = 12;
	coord->dir_x = 0;
	coord->dir_y = 1;
	coord->plane_x = rotate_vector(coord->dir_x, coord->dir_y, -PI / 2, 'x');
	coord->plane_y = rotate_vector(coord->dir_x, coord->dir_y, -PI / 2, 'y');
}

int	main(void)
{
	int			**map;
	t_coords	coord;
	t_data		*data;

	map = parce_map();
	init_coords(&coord);
	data = init_data();
	render_loop(data, &coord, map);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->mlx_img, 0, 0);
	mlx_loop(data->mlx);


}
