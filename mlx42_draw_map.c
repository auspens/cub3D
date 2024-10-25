
#include "cub3d.h"

void	error_exit(t_map *mapdata)
{
	ft_printf("%s", mlx_strerror(mlx_errno));
	if (mapdata->txtr)
	{
		if (mapdata->img)
			mlx_delete_image(mapdata->mlx, mapdata->img);
		delete_textures(mapdata->txtr);
	}
	if (mapdata->mlx)
		mlx_terminate(mapdata->mlx);
	free_map(mapdata->map);
	exit(EXIT_FAILURE);
}

int32_t	draw_map(t_map *md)
{
	t_tx	txtr;

	md->mlx = mlx_init(screenWidth, screenHeight, "cub", false);
	if (!md->mlx)
		error_exit(md);
	init_txtr(md, &txtr);
	md->img = mlx_new_image(md->mlx, screenWidth, screenHeight);
	if (!md->img || (mlx_image_to_window(md->mlx, md->img, 0, 0) < 0))
		error_exit(md);
	hook(md);
	//mlx_key_hook(md->mlx, &key_hook, md);
	//mlx_loop_hook(md->mlx, &hook, md);
	mlx_loop(md->mlx);
	mlx_delete_image(md->mlx, md->img);
	delete_textures(&txtr);
	mlx_terminate(md->mlx);
	free_map(md->map);
	return (EXIT_SUCCESS);
}

/*
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*md;

	md = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(md->mlx);
	if (md->exit)
		return ;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_left(md);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_up(md);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_right(md);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_down(md);
}
*/ 

void	hook(void *param)
{
	t_map	*md;

	md = param;

	double 	rel_pos;
	double	ray_x;
	double	ray_y;
	int		map_x;
	int 	map_y;
	double side_dist_x;
	double side_dist_y;

	double delta_x;
	double delta_y;
	double camera_to_wall;

	int step_x;
	int step_y;

	int hit;
	int side;

	int line_h;
	
	int x = -1;
	while(++x < screenWidth)
	{
		printf("in the loop for x = %i\n", x);
		rel_pos = 2 * x / (double)screenWidth - 1;
		ray_x = md->dirx + md->planex * rel_pos;
		ray_y = md->diry + md->planey * rel_pos;

		delta_x = DBL_MAX;
		if (ray_x)
			delta_x = fabs(1 / ray_x);
		delta_y = DBL_MAX;
		if (ray_y)
			delta_y = fabs(1 / ray_y);
		map_x = (int)md->px;
		map_y = (int)md->py;
		if (ray_x < 0)
		{
			step_x = -1;
			side_dist_x = (md->px - map_x) * delta_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1 - md->px) * delta_x;
		}
		if (ray_y < 0)
		{
			step_y = -1;
			side_dist_y = (md->py - map_y) * delta_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1 - md->py) * delta_y;
		}
		hit = 0;
		side = 0;
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_y;
				map_y += step_y;
				side = 1;
			}
			if (md->map[map_y][map_x] != '0')
				hit = 1;
		}
		if (side == 0)
			camera_to_wall = side_dist_x - delta_x;
		else
			camera_to_wall = side_dist_y - delta_y;
		if (camera_to_wall < 1)
			line_h = screenHeight;
		else
			line_h = (int)(screenHeight / camera_to_wall);
		printf("line height is %i\n", line_h);
		draw_line(md, x, line_h, side, hit);
	}
}
