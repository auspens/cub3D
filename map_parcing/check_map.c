/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:44:51 by auspensk          #+#    #+#             */
/*   Updated: 2024/12/09 11:46:22 by auspensk         ###   ########.fr       */
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
	return (i);
}

void	trim_newlines(t_data *data)
{
	int	y;
	int	map_ended;

	y = -1;
	map_ended = 0;
	while (data->map[++y])
	{
		if (map_ended && data->map[y][0] != '\n')
		{
			while (data->map[y])
			{
				free(data->map[y]);
				data->map[y] = NULL;
				y++;
			}
			clean_exit(1, "Error parcing the map\n", data);
		}
		if (data->map[y][0] == '\n')
		{
			free(data->map[y]);
			data->map[y] = NULL;
			map_ended = 1;
		}
	}
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


void	check_char_value(t_data *data, int x, int y, char c)
{
	if (should_be_wall(data, x, y) && c != '1' && c != ' ')
		clean_exit(1, "Err: map has to be surrounded by walls\n", data);
	if (!should_be_wall(data, x, y))
	{
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			set_player(data, x, y);
		else if (c != '0' && c != '1' && c != ' ')
			return (clean_exit
				(1, "Err: not allowed chars in map\n", data));
	}
}

void	check_valid_map(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	trim_newlines(data);
	while (data->map[++y])
	{
		while (data->map[y][++x] && data->map[y][x] != '\n')
			check_char_value(data, x, y, data->map[y][x]);
		x = -1;
	}
	if (data->player.x == 0)
		clean_exit(1, "Err: player not set on the map\n", data);
}
