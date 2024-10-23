/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:01:38 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/23 16:27:00 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perform_dda(int	**map, t_data_x *data_x)
{
	while (!data_x->hit)
	{
		if (data_x->side_dist_x < data_x->side_dist_y)
		{
			data_x->side_dist_x += data_x->del_dist_x;
			data_x->map_x += data_x->step_x;
			if (data_x->step_x == -1)
				data_x->side = WEST;
			else
				data_x->side = EAST;
		}
		else
		{
			data_x->side_dist_y += data_x->del_dist_y;
			data_x->map_y += data_x->step_y;
			if (data_x->step_y == -1)
				data_x->side = SOUTH;
			else
				data_x->side = NORTH;
		}
		if (map[data_x->map_x][data_x->map_y])
			data_x->hit = map[data_x->map_x][data_x->map_y];
	}
}

void	draw_line_to_img(t_img_data *data, t_data_x *data_x, int x)
{
	int	y;

	y = -1;
	while (++y < SCRNHEIGHT)
	{
		if (y < data_x->draw_start)
			my_pixel_put(data, x, y, get_color(CEILING));
		else if (y < data_x->draw_end)
			my_pixel_put(data, x, y, data_x->side);
		else
			my_pixel_put(data, x, y, FLOOR);
	}
}

int	render_loop(t_data *data, t_coords *coords, int **map)
{
	int			x;
	t_data_x	data_x;

	x = -1;
	while (1)
	{
		while (++x < SCRNWIDTH)
		{
			calc_data_x(coords, &data_x, x);
			perform_dda(map, &data_x);
			calc_perp_wall_dist(&data_x);
			calc_line_height(&data_x);
			draw_line_to_img(data->img, &data_x, x);
		}
		break;
	}
	return (0);
}
