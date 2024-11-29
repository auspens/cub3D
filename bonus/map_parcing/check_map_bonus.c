/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:44:51 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/29 14:41:18 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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

void	check_char_value(t_data *data, int x, int y, char c)
{
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

void	check_valid_map(t_data *data)
{
	int		x;
	int		y;

	y = -1;
	trim_newlines(data);
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x] && data->map[y][x] != '\n')
			check_char_value(data, x, y, data->map[y][x]);
	}
}
