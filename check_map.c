
#include "cub3d.h"

int	check_valid_map(t_data *data)
{
	int		idx;
	int		res;
	char	*line;
	int		width;

	line = data->map[0];
	idx = -1;
	while (line[++idx] && line[idx] != '\n')
	{
		if (line[idx] != '1')
			map_error(0, data, NULL, 2);
	}
	width = idx;
	res = check_other_lines(data, width, 0);
	if (res != 0)
		map_error(0, data, NULL, res);
	if (!data->player.x || !data->player.y)
		map_error(0, data, NULL, 4);
	return (0);
}

int	check_other_lines(t_data *data, int width, int height)
{
	char	*line;
	int		lnum;
	int		idx;
	int		res;

	lnum = 1;
	res = 0;
	line = data->map[lnum];
	while (line)
	{
		idx = -1;
		while (!res && ++idx < width)
			res = check_char(data, line, idx, lnum, width);
		if (!res && line[idx] && line[idx] != '\n')
			res = 1;
		if (res != 0)
			return (res);
		line = data->map[++lnum];
	}
	height = lnum;
	return (check_last_line(data, lnum - 1, width));
}

int	check_last_line(t_data *data, int num, int width)
{
	char	*line;
	int		idx;

	line = data->map[num];
	idx = -1;
	while (++idx < width)
	{
		if (!line[idx] || line[idx] != '1')
			return (1);
	}
	if (line[idx] && line[idx] != '\n')
		return (1);
	return (0);
}

int	check_char(t_data *data, char *line, int idx, int lnum, int width)
{
	if (!line[idx] || line[idx] == '\n')
		return (1);
	if ((idx == 0 || idx == width - 1) && line[idx] != '1')
		return (1);
	if (line[idx] == 'P')
	{
		if (data->player.x != 0)
			return (2);
		data->player.x = (double)idx + 0.5;
		data->player.y = (double)lnum + 0.5;
		line[idx] = '0';
	}
	else if (line[idx] != '0' && line[idx] != '1')
		return (3);
	return (0);
}
