/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_color_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:07:37 by auspensk          #+#    #+#             */
/*   Updated: 2024/12/09 13:24:50 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	exit_at_reading_color(t_data *data, int fd, char **arr)
{
	free_array(arr);
	close(fd);
	clean_exit(1, "Map error in colors\n", data);
}

int	read_color(char *line, int *rgb)
{
	int		i;
	char	color[4];

	i = -1;
	while (ft_isdigit(line[++i]) && i < 4)
		color[i] = line[i];
	if (i < 1 || i > 4)
		return (-1);
	color[i] = '\0';
	*rgb = ft_atoi(color);
	if (*rgb < 0 || *rgb > 255)
		return (-1);
	return (i);
}

int	check_color(t_data *data, char **lines, int fd)
{
	int	i;
	int	c_i;
	int	c_move;
	int	rgb[3];

	i = -1;
	c_i = 0;
	while ((lines[1][c_i]))
	{
		i ++;
		c_move = read_color(&(lines[1][c_i]), &(rgb[i]));
		if (c_move == -1)
			exit_at_reading_color(data, fd, lines);
		c_i += c_move;
		if (lines[1][c_i] == ',' && i < 2)
			c_i++;
		else if (lines[1][c_i] != '\0')
			exit_at_reading_color(data, fd, lines);
	}
	if (i != 2)
		exit_at_reading_color(data, fd, lines);
	return (gen_trgb(255, rgb[0], rgb[1], rgb[2]));
}

int	parce_color(t_data *data, char **lines, int fd)
{
	if (!lines[1] || lines[2])
		exit_at_reading_color(data, fd, lines);
	if (!ft_strcmp(lines[0], "F"))
	{
		if (data->color_floor)
			exit_at_reading_color(data, fd, lines);
		data->color_floor = check_color(data, lines, fd);
	}
	if (!ft_strcmp(lines[0], "C"))
	{
		if (data->color_ceiling)
			exit_at_reading_color(data, fd, lines);
		data->color_ceiling = check_color(data, lines, fd);
	}
	free_array(lines);
	return (1);
}
