/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_render_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:28:10 by auspensk          #+#    #+#             */
/*   Updated: 2024/12/02 10:16:18 by eusatiko         ###   ########.fr       */
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

t_door	*find_door(t_data *data, int x, int y)
{
	int		i;

	i = -1;
	while (++i < 24 && data->doors[i].x)
	{
		if (data->doors[i].x == x)
		{
			if (data->doors[i].y == y)
				return (&data->doors[i]);
		}
	}
	return (NULL);
}

void	handle_door(t_dda dda, t_draw_data *draw, t_data *data, t_ray ray)
{
	int		can_see_further;
	t_door	*door;

	door = find_door(data, dda.map_x, dda.map_y);
	if (!door)
		return ;
	draw->txtr = door->txtr;
	if (door->state)
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
		draw->txtr_x += door->open_ratio * (double)draw->txtr->width;
	else if (door->state == 0 && dist_to_door(data->player, dda) < 2.5)
		data->can_open = door;
}
