
#include "cub3d.h"

void	free_map(char **map)
{
	int	idx;

	idx = 0;
	if (!map)
		return ;
	while (map[idx])
		free(map[idx++]);
	free(map);
}
