/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:25:29 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/27 11:42:34 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_error(int fd, t_data *data, char *line, int error)
{
	if (fd)
		close(fd);
	if (line)
		free(line);
	if (error == -1)
		clean_exit(1, "Error: failed to allocate space on the heap\n", data);
	else if (error == 1)
	{
		clean_exit(1,
			"Error: the map has to be rectangular, surroundedby walls\n", data);
	}
	else if (error == 2)
		clean_exit(1, "Error: there can be only 1 player (P)\n", data);
	else if (error == 3)
		clean_exit(1, "Error: only characters 0, 1 and P are allowed\n", data);
	else if (error == 4)
		clean_exit(1, "Error: there has to be 1 player (P)\n", data);
	exit(EXIT_FAILURE);
}
