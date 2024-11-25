/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_items.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:05:04 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/25 11:30:26 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_player(t_data *data, int x, int y)
{
	if (data->player.x != 0)
		clean_exit(1, "Err: more than one player\n", data);
	data->player.x = (double)x + 0.5;
	data->player.y = (double)y + 0.5;
	set_direction(data, data->map[y][x]);
	data->plane = rotate_vector(data->dir, PI / 2);
	data->plane.x *= 0.66;
	data->plane.y *= 0.66;
	data->map[y][x] = '0';
}

