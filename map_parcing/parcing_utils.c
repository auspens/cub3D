/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:15:07 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/13 16:18:02 by auspensk         ###   ########.fr       */
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

void	trim_newlines(t_data *data)
{
	int	y;
	int	map_ended;

	y = -1;
	map_ended = 0;
	while (data->map[++y])
	{
		if (map_ended && data->map[y][0] != '\n')
			clean_exit(1, "Err: newline inside the map\n", data);
		if (data->map[y][0] == '\n')
		{
			data->map[y] = NULL;
			map_ended = 1;
		}
	}
}
