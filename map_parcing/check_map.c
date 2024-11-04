/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleonora <eleonora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:44:51 by auspensk          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/04 14:38:17 by eleonora         ###   ########.fr       */
=======
/*   Updated: 2024/11/01 11:50:02 by auspensk         ###   ########.fr       */
>>>>>>> origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	should_be_wall(t_data *data, int x, int y)
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

void	check_valid_map(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (data->map[++y])
	{
		while (data->map[y][++x] && data->map[y][x] != '\n')
		{
			if (should_be_wall(data, x, y) && data->map[y][x] != '1')
				clean_exit(1, "Err: map has to be surrounded by walls\n", data);
			if (!should_be_wall(data, x, y))
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
