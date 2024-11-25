/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:49:38 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/25 15:44:21 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	door_closing(t_data *data, t_door *door)
{
	door->open_ratio -= data->elapsed;
	if (door->open_ratio <= 0)
	{
		door->open_ratio = 0;
		door->state = 0;
	}
	data->redraw = 1;
}

void	door_opening(t_data *data, t_door *door)
{
	door->open_ratio += data->elapsed;
	if (door->open_ratio >= 1)
	{
		door->open_ratio = 1;
		door->state = 2;
		door->tm_stamp = data->oldtime.tv_sec;
	}
	data->redraw = 1;
}

void	iter_doors(t_data *data)
{
	int		i;
	t_door	*door;

	i = -1;
	while (++i < data->num_drs)
	{
		door = &data->doors[i];
		if (door->state == 1)
			door_opening(data, door);
		if (door->state == 2)
		{
			if (data->oldtime.tv_sec - door->tm_stamp > 5
				&& ((int)data->player.x != door->x
					|| (int)data->player.y != door->y))
				door->state = 3;
		}
		if (door->state == 3)
			door_closing(data, door);
	}
}
