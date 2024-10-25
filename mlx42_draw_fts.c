
#include "cub3d.h"

void	draw_line(t_map *md, int x, int height, int side, int hit)
{
	int			y;
	uint32_t	color;

	(void)hit;
	if (side)
		color = 0xFF0000FF;
	else
		color = 0x00FF00FF;

	int line_lowest_p = screenHeight / 2 - height / 2;
	int line_highest_p = screenHeight / 2 + height / 2;

	y = line_lowest_p;
	while (y < line_highest_p + 1)
	{
		mlx_put_pixel(md->img, x, y, color);
		y++;
	}
}
