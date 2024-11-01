/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:07:37 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/01 14:32:51 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	read_color(t_data *data, char **lines, int fd, char **colors)
{
	int	rgb[3];
	int	ind;

	ind = -1;
	while (colors[++ind])
	{
		if (!ft_isnum(colors[ind]))
		{
			free_array(colors);
			exit_at_reading_input(data, fd, lines, "Map error in colors\n");
		}
		rgb[ind] = ft_atoi(colors[ind]);
		if (rgb[ind] > 255 || rgb[ind] < 0)
		{
			free_array(colors);
			exit_at_reading_input(data, fd, lines, "Map error in colors\n");
		}
	}
	if (ind != 3)
		exit_at_reading_input(data, fd, lines, "Map error in colors\n");
	return (gen_trgb(255, rgb[0], rgb[1], rgb[2]));
}

int	parce_color(t_data *data, char **lines, int fd)
{
	// int		rgb[3];
	// int		ind;
	char	**colors;

	if (!lines[1] || lines[2])
		exit_at_reading_input(data, fd, lines, "Map error in colors\n");
	// ind = -1;
	colors = ft_split(lines[1], ',');
	// while (colors[++ind])
	// {
	// 	if (!ft_isnum(colors[ind]))
	// 		exit_at_reading_input(data, fd, lines, "Map error in colors\n");
	// 	rgb[ind] = ft_atoi(colors[ind]);
	// 	if (rgb[ind] > 255 || rgb[ind] < 0)
	// 		exit_at_reading_input(data, fd, lines, "Map error in colors\n");
	// }
	// if (ind != 2)
	// 	exit_at_reading_input(data, fd, lines, "Map error in colors\n");
	if (!ft_strcmp(lines[0], "F"))
	{
		if (data->color_floor)
			exit_at_reading_input(data, fd, lines, "Map error in colors\n");
		data->color_floor = read_color(data, lines, fd, colors);
	}
	if (!ft_strcmp(lines[0], "C"))
	{
		if (data->color_ceiling)
			exit_at_reading_input(data, fd, lines, "Map error in colors\n");
		data->color_ceiling = read_color(data, lines, fd, colors);
	}
	return (1);
}
