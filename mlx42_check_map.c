
#include "cub3d.h"

int	check_valid_map(t_map *mapdata)
{
	int		idx;
	int		res;
	char	*line;

	line = mapdata->map[0];
	idx = -1;
	while (line[++idx] && line[idx] != '\n')
	{
		if (line[idx] != '1')
			return (2);
	}
	mapdata->width = idx;
	res = check_other_lines(mapdata);
	if (res != 0)
		return (res);
	if (!mapdata->player.x || !mapdata->player.y)
		return (4);
	return (0);
}

int	check_other_lines(t_map *mapdata)
{
	char	*line;
	int		lnum;
	int		idx;
	int		res;

	lnum = 1;
	res = 0;
	line = mapdata->map[lnum];
	while (line)
	{
		idx = -1;
		while (!res && ++idx < mapdata->width)
			res = check_char(mapdata, line, idx, lnum);
		if (!res && line[idx] && line[idx] != '\n')
			res = 1;
		if (res != 0)
			return (res);
		line = mapdata->map[++lnum];
	}
	mapdata->height = lnum;
	return (check_last_line(mapdata, lnum - 1));
}

int	check_last_line(t_map *mapdata, int num)
{
	char	*line;
	int		idx;

	line = mapdata->map[num];
	idx = -1;
	while (++idx < mapdata->width)
	{
		if (!line[idx] || line[idx] != '1')
			return (1);
	}
	if (line[idx] && line[idx] != '\n')
		return (1);
	return (0);
}

int	check_char(t_map *mapdata, char *line, int idx, int lnum)
{
	if (!line[idx] || line[idx] == '\n')
		return (1);
	if ((idx == 0 || idx == mapdata->width - 1) && line[idx] != '1')
		return (1);
	if (line[idx] == 'P')
	{
		if (mapdata->player.x != 0)
			return (2);
		mapdata->player.x = (double)idx + 0.5;
		mapdata->player.y = (double)lnum + 0.5;
		line[idx] = '0';
	}
	else if (line[idx] != '0' && line[idx] != '1')
		return (3);
	return (0);
}
