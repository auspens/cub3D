/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_items_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:05:04 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/29 14:58:00 by auspensk         ###   ########.fr       */
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

char	*get_d_txtr_path(int num_dr)
{
	char	*num;
	char	*name;
	char	*path;

	if (num_dr > 3)
		path = ft_strdup("./textures/d.xpm");
	else
	{
		num = ft_itoa(num_dr);
		if (!num)
			return (NULL);
		name = ft_strjoin("./textures/d", num);
		if (!name)
		{
			free(num);
			return (NULL);
		}
		path = ft_strjoin(name, ".xpm");
		free(num);
		free(name);
	}
	return (path);
}

void	set_sprite(t_data *data, int x, int y, t_door *door)
{
	int	sprite_fail;

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
		perror("Sprite texture");
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
	char	*path;

	if (data->num_drs == 24)
		clean_exit (1, "Err: too many doors\n", data);
	door = &data->doors[data->num_drs];
	door->x = x;
	door->y = y;
	door->state = 0;
	door->open_ratio = 0;
	door->tm_stamp = 0;
	data->num_drs++;
	path = get_d_txtr_path(data->num_drs);
	if (!path)
		clean_exit (1, "Err: failed memory allocation\n", data);
	if (get_texture(path, data, &door->txtr) == 1)
	{
		perror(path);
		free(path);
		clean_exit(1, NULL, data);
	}
	set_sprite(data, x, y, door);
	free(path);
}
