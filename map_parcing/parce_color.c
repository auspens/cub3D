/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:07:37 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/29 11:23:18 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	exit_at_reading_color(t_data *data, int fd, char **arr, char **colors)
{
	if (colors)
		free_array(colors);
	free_array(arr);
	close(fd);
	clean_exit(1, "Map error in colors\n", data);
}

int	read_color(t_data *data, char **lines, int fd, char **colors)
{
	int	rgb[3];
	int	ind;

	ind = -1;
	while (colors[++ind])
	{
		if (!ft_isnum(colors[ind]))
			exit_at_reading_color(data, fd, lines, colors);
		rgb[ind] = ft_atoi(colors[ind]);
		if (rgb[ind] > 255 || rgb[ind] < 0)
			exit_at_reading_color(data, fd, lines, colors);
	}
	if (ind != 3)
		exit_at_reading_color(data, fd, lines, colors);
	return (gen_trgb(255, rgb[0], rgb[1], rgb[2]));
}

int	parce_color(t_data *data, char **lines, int fd)
{
	char	**colors;

	if (!lines[1] || lines[2])
		exit_at_reading_color(data, fd, lines, NULL);
	colors = ft_split(lines[1], ',');
	if (!ft_strcmp(lines[0], "F"))
	{
		if (data->color_floor)
			exit_at_reading_color(data, fd, lines, colors);
		data->color_floor = read_color(data, lines, fd, colors);
	}
	if (!ft_strcmp(lines[0], "C"))
	{
		if (data->color_ceiling)
			exit_at_reading_color(data, fd, lines, colors);
		data->color_ceiling = read_color(data, lines, fd, colors);
	}
	free_array(lines);
	free_array(colors);
	return (1);
}
