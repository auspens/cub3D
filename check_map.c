/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:44:51 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/28 11:45:37 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	should_be_one(t_data *data, int x, int y)
{
	if (x == 0 || data->map[y][x + 1] == '\n' || data->map[y][x + 1] == ' '
		|| data->map[y][x - 1] == ' ')
		return (1);
	if (data->map[y + 1] == NULL || y == 0 || data->map[y - 1][x] == ' '
		|| data->map[y - 1][x] == ' ')
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
		data->dir.y = 1;
	}
	if (c == 'S')
	{
		data->dir.x = 0;
		data->dir.y = -1;
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
	rotate_vector(data->dir, &(data->plane), -PI / 2);
	data->map[y][x] = '0';
}

void	check_valid_map(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (data->map[++y])
	{
		while (data->map[y][++x] != '\n')
		{
			if (should_be_one(data, x, y) && data->map[y][x] != '1')
				clean_exit(1, "Err: map has to be surrounded by walls\n", data);
			if (!should_be_one(data, x, y))
			{
				if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
					|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
					set_player(data, x, y);
				else if (data->map[y][x] != '0' && data->map[y][x] != '1'
					&& data->map[y][x] != ' ')
					return (clean_exit
						(1, "Err: not allowed chars in map\n", data));
			}
		}
		x = -1;
	}
}

// int	check_valid_map(t_data *data)
// {
// 	int		idx;
// 	int		res;
// 	char	*line;
// 	int		width;

// 	line = data->map[0];
// 	idx = -1;
// 	while (line[++idx] && line[idx] != '\n')
// 	{
// 		if (line[idx] != '1')
// 			map_error(0, data, NULL, 2);
// 	}
// 	width = idx;
// 	res = check_other_lines(data, width, 0);
// 	if (res != 0)
// 		map_error(0, data, NULL, res);
// 	if (!data->player.x || !data->player.y)
// 		map_error(0, data, NULL, 4);
// 	return (0);
// }

// int	check_other_lines(t_data *data, int width, int height)
// {
// 	char	*line;
// 	int		lnum;
// 	int		idx;
// 	int		res;

// 	lnum = 1;
// 	res = 0;
// 	line = data->map[lnum];
// 	while (line)
// 	{
// 		idx = -1;
// 		while (!res && ++idx < width)
// 			res = check_char(data, line, idx, lnum, width);
// 		if (!res && line[idx] && line[idx] != '\n')
// 			res = 1;
// 		if (res != 0)
// 			return (res);
// 		line = data->map[++lnum];
// 	}
// 	height = lnum;
// 	return (check_last_line(data, lnum - 1, width));
// }

// int	check_last_line(t_data *data, int num, int width)
// {
// 	char	*line;
// 	int		idx;

// 	line = data->map[num];
// 	idx = -1;
// 	while (++idx < width)
// 	{
// 		if (!line[idx] || line[idx] != '1')
// 			return (1);
// 	}
// 	if (line[idx] && line[idx] != '\n')
// 		return (1);
// 	return (0);
// }

// int	check_char(t_data *data, char *line, int idx, int lnum, int width)
// {
// 	if (!line[idx] || line[idx] == '\n')
// 		return (1);
// 	if ((idx == 0 || idx == width - 1) && line[idx] != '1')
// 		return (1);
// 	if (line[idx] == 'P')
// 	{
// 		if (data->player.x != 0)
// 			return (2);
// 		data->player.x = (double)idx + 0.5;
// 		data->player.y = (double)lnum + 0.5;
// 		line[idx] = '0';
// 	}
// 	else if (line[idx] != '0' && line[idx] != '1')
// 		return (3);
// 	return (0);
// }
