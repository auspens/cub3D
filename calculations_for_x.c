/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_for_x.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:46:07 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/23 16:09:34 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_step_and_side_dist(t_coords *coords, t_data_x *data_x)
{
	if (data_x->ray_x < 0)
	{
		data_x->step_x = -1;
		data_x->side_dist_x = (coords->pos_x - data_x->map_x)
			* data_x->del_dist_x;
	}
	else
	{
		data_x->step_x = 1;
		data_x->side_dist_x = (data_x->map_x + 1.0 - coords->pos_x)
			*data_x->del_dist_x;
	}
	if (data_x->ray_y < 0)
	{
		data_x->step_y = -1;
		data_x->side_dist_y = (coords->pos_y - data_x->map_y)
			* data_x->del_dist_y;
	}
	else
	{
		data_x->step_y = 1;
		data_x->side_dist_y = (data_x->map_y + 1.0 - coords->pos_y)
			* data_x->del_dist_y;
	}
}

void	calc_perp_wall_dist(t_data_x *data_x)
{
	if (data_x->side == EAST || data_x->side == WEST)
		data_x->perp_wall_dist = data_x->side_dist_x - data_x->del_dist_x;
	else
		data_x->perp_wall_dist = data_x->side_dist_y - data_x->del_dist_y;
}

void	calc_data_x(t_coords *coords, t_data_x *data_x, int x)
{
	data_x->map_x = coords->pos_x;
	data_x->map_y = coords->pos_y;
	data_x->cam_x = 2 * x / (double) SCRNWIDTH - 1;
	data_x->ray_x = coords->dir_x + coords->plane_x * data_x->cam_x;
	data_x->ray_y = coords->dir_y + coords->plane_y * data_x->cam_x;
	if (data_x->ray_x == 0)
		data_x->del_dist_x = 1e30;
	else
		data_x->del_dist_x = fabs(1 / data_x->ray_x);
	if (data_x->ray_y == 0)
		data_x->del_dist_y = 1e30;
	else
		data_x->del_dist_y = fabs(1 / data_x->del_dist_y);
	data_x->hit = 0;
	calc_step_and_side_dist(coords, data_x);
}

void	calc_line_height(t_data_x *data_x)
{
	data_x->line_height = (int)(SCRNHEIGHT / data_x->perp_wall_dist);
	data_x->draw_start = -data_x->line_height / 2 + SCRNHEIGHT / 2;
	data_x->draw_end = data_x->line_height / 2 + SCRNHEIGHT / 2;
}
