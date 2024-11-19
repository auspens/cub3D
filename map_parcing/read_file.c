/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:05:04 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/19 11:54:33 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	open_mapfile(char *path)
{
	int	fd;
	int	len;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
		clean_exit(1, "Error: map file has to be of format *.cub\n", NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error: ");
		clean_exit(1, NULL, NULL);
	}
	return (fd);
}

int	read_texture(char **lines, t_data *data, int fd)
{
	int	res;

	res = 0;
	if (!ft_strcmp(lines[0], "NO"))
		res = get_texture(lines[1], data, &(data->txt->n));
	if (!ft_strcmp(lines[0], "SO"))
		res = get_texture(lines[1], data, &(data->txt->s));
	if (!ft_strcmp(lines[0], "EA"))
		res = get_texture(lines[1], data, &(data->txt->e));
	if (!ft_strcmp(lines[0], "WE"))
		res = get_texture(lines[1], data, &(data->txt->w));
	if (res || lines[2])
	{
		free_array(lines);
		close(fd);
		clean_exit(1, "Err: incorrect input in textures\n", data);
	}
	free_array(lines);
	return (1);
}

int	check_line(char *line, t_data *data, int fd)
{
	char	**split_line;
	char	*trimmed_line;

	if (*line == '\n')
	{
		free(line);
		return (0);
	}
	trimmed_line = ft_strtrim(line, " \n");
	split_line = ft_split(trimmed_line, ' ');
	free (line);
	free(trimmed_line);
	if (!ft_strcmp(split_line[0], "NO") || !ft_strcmp(split_line[0], "SO")
		|| !ft_strcmp(split_line[0], "WE") || !ft_strcmp(split_line[0], "EA"))
		return (read_texture(split_line, data, fd));
	else if (!ft_strcmp(split_line[0], "F") || !ft_strcmp(split_line[0], "C"))
		return (parce_color(data, split_line, fd));
	else
	{
		free_array(split_line);
		close(fd);
		clean_exit(1, "Err: incorrect input in textures and colors\n", data);
	}
	free_array(split_line);
	return (0);
}

void	get_input(t_data *data, int fd, int size)
{
	int		idx;
	char	*line;

	idx = 0;
	line = get_next_line(fd);
	while (idx < 6)
	{
		idx += check_line(line, data, fd);
		line = get_next_line(fd);
	}
	while (*line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	get_map(data, line, fd, size);
	get_texture("./textures/abstract.xpm\n", data, &(data->txt->dr)); //looks weird here, should we include this in the map?
	get_texture("./textures/gift.xpm\n", data, &(data->sprite.txtr));
}

void	get_map(t_data *data, char *line, int fd, int size)
{
	int		idx;
	char	**newmap;

	newmap = ft_calloc(size + 1, sizeof(char *));
	if (!newmap)
		newmap_error(fd, data, line);
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
