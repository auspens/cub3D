/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:05:04 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/27 16:14:06 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_mapfile(char *path)
{
	int	fd;
	int	len;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
		clean_exit(1, "Error: map file has to be of format *.ber\n", NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error: ");
		clean_exit(1, NULL, NULL);
	}
	return (fd);
}

void	get_input(t_data *data, int fd, int size)
{
	int		idx;
	char	*line;

	idx = -1;
	line = get_next_line(fd);
	/*here add a function to analyse the contents of the line*/
	// while (line && ++idx < size)
	// {
	// 	data->map[idx] = line;
	// 	line = get_next_line(fd);
	// 	/*here add a function to analyse the contents of the line
	// 	and switch to get_map when the map starts*/
	// }
	/*temp fix*/
	// data->txt->s = get_texture("./textures/S.xpm");
	// data->txt->n = get_texture("./textures/N.xpm");
	// data->txt->e = get_texture("./textures/E.xpm");
	// data->txt->w = get_texture("./textures/W.xpm");
	get_map(data, line, fd, size);
	data->color_ceiling = gen_trgb(255, 56, 178, 239);
	data->color_floor = gen_trgb(255, 63, 193, 37);
}

void	get_map(t_data *data, char *line, int fd, int size)
{
	int		idx;
	char	**newmap;

	newmap = ft_calloc(size + 1, sizeof(char *));
	if (!newmap)
		map_error(fd, data, line, -1);
	idx = -1;
	if (data->map)
	{
		while (data->map[++idx])
			newmap[idx] = data->map[idx];
		idx--;
		free(data->map);
	}
	data->map = newmap;
	if (!line)
		line = get_next_line(fd);
	while (line && ++idx < size)
	{
		data->map[idx] = line;
		line = get_next_line(fd);
	}
	if (line)
		get_map(data, line, fd, size * 2);
}
