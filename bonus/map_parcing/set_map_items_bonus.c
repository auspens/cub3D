/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_items_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:05:04 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/29 12:14:27 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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

void	set_sprite(t_data *data, int x, int y, t_door *door)
{
	int		sprite_fail;

	door->sprite.pos.x = x + 0.5;
	door->sprite.pos.y = y + 0.5;
	if (data->num_drs % 2 == 1)
		sprite_fail = get_texture("./textures/ducky.xpm\n",
				data, &(door->sprite.t));
	else
		sprite_fail = get_texture("./textures/tree.xpm\n",
				data, &(door->sprite.t));
	if (sprite_fail)
	{
		perror("Failed to read sprite texture");
		clean_exit(1, NULL, data);
	}
	door->sprite.size = door->sprite.t->height;
	door->sprite.moves = door->sprite.t->width / door->sprite.size;
	door->sprite.scale = 128 / door->sprite.size;
	if (door->sprite.scale < 1)
		door->sprite.scale = 1;
}

void	set_door(t_data *data, int x, int y)
{
	t_door	*door;

	door = &data->doors[data->num_drs];
	door->x = x;
	door->y = y;
	door->state = 0;
	door->open_ratio = 0;
	door->tm_stamp = 0;
	data->num_drs++;
	set_sprite(data, x, y, door);
}
