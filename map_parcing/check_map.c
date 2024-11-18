/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:44:51 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/18 09:47:44 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	char_ind(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

int	should_be_wall(t_data *data, int x, int y)
{
	int	ind;

	if (y)
	{
		ind = char_ind(data->map[y - 1], '\n');
		if (ind <= x + 1)
			return (1);
	}
	if (data->map[y + 1])
	{
		ind = char_ind(data->map[y + 1], '\n');
		if (ind <= x + 1)
			return (1);
	}
	if (x == 0 || data->map[y][x + 1] == '\n' || data->map[y][x + 1] == ' '
		|| data->map[y][x - 1] == ' ')
		return (1);
	if (data->map[y + 1] == NULL || y == 0 || data->map[y - 1][x] == ' '
		|| data->map[y + 1][x] == ' ')
		return (1);
	if (data->map[y + 1][x + 1] == ' ' || data->map[y - 1][x - 1] == ' '
		|| data->map[y - 1][x + 1] == ' ' || data->map[y + 1][x - 1] == ' ')
		return (1);
	return (0);
}

void	set_direction(t_data *data, char c)
{
	if (c == 'N')
	{
		data->dir.x = 0;
		data->dir.y = -1;
	}
	if (c == 'S')
	{
		data->dir.x = 0;
		data->dir.y = 1;
	}
	if (c == 'E')
	{
		data->dir.x = 1;
		data->dir.y = 0;
	}
	if (c == 'W')
	{
		data->dir.x = -1;
		data->dir.y = 0;
	}
}

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

void	set_door(t_data *data, int x, int y)
{
	t_door *door;

	door = &data->doors[data->num_drs];
	door->x = x;
	door->y = y;
	door->state = 0;
	door->open_ratio = 0;
	door->timer = 0;
	data->num_drs++;
}

void	check_valid_map(t_data *data)
{
	int	x;
	int	y;
	char c;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x] && data->map[y][x] != '\n')
		{
			c = data->map[y][x];
			if (should_be_wall(data, x, y) && (c != '1' && c != ' '))
				clean_exit(1, "Err: map has to be surrounded by walls\n", data);
			if (!should_be_wall(data, x, y))
			{
				if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
					set_player(data, x, y);
				else if (c == 'D')
					set_door(data, x, y);
				else if (c != '0' && c != '1' && c != ' ')
					clean_exit(1, "Err: not allowed chars in map\n", data);
			}
		}
	}
}
