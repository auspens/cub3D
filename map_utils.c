/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:25:29 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/29 12:44:17 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_error(int fd, t_data *data, char *line)
{
	if (fd)
		close(fd);
	if (line)
		free(line);
	clean_exit(1, "Error: failed to allocate space on the heap\n", data);
}
