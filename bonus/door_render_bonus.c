/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_render_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:28:10 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/25 15:44:17 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_door_state(t_draw_data *draw, t_door *door, t_sides side)
{
	if (door->state == 2)
		return (1);
	if (door->state == 0)
		return (0);
	if (side == NORTH || side == EAST)
	{
		if (draw->wall_x > 1 - door->open_ratio)
			return (1);
	}
	else
	{
		if (draw->wall_x < door->open_ratio)
			return (1);
	}
	return (0);
}

float	dist_to_door(t_coord player, t_dda dda)
{
	float	dist;

	if (dda.side == EAST || dda.side == WEST)
		dist = fabs(player.x - dda.map_x);
	else
		dist = fabs(player.y - dda.map_y);
	return (dist);
}

void	handle_door(t_dda dda, t_draw_data *draw, t_data *data, t_ray ray)
{
	int		can_see_further;
	int		i;
	t_door	*door;

	i = -1;
	door = NULL;
	while (++i < 24 && data->doors[i].x)
	{
		if (data->doors[i].x == dda.map_x)
		{
			if (data->doors[i].y == dda.map_y)
				door = &data->doors[i];
		}
	}
	if (door && door->state)
		data->sprite = &door->sprite;
	can_see_further = check_door_state(draw, door, dda.side);
	if (can_see_further)
	{
		dda.hit = 0;
		perform_dda(&dda, data->map);
		calc_line_height(dda, draw);
		calc_wall_txtr_x(dda, draw, data, ray);
		return ;
	}
	if (door->state == 1 || door->state == 3)
	{
		//if (dda.side == NORTH || dda.side == EAST)
		draw->txtr_x += door->open_ratio * (double)draw->txtr->width;
	}
	else if (door->state == 0 && dist_to_door(data->player, dda) < 2.5)
		data->can_open = door;
}
