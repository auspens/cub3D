
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
	draw_frame(md);
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


t_ray init_ray(t_map *md, int x)
{
	t_ray ray;

	double rel_pos = 2 * x / (double)screenWidth - 1;
	ray.dir.x = md->dir.x + md->plane.x * rel_pos;
	ray.dir.y = md->dir.y + md->plane.y * rel_pos;
	ray.origin.x = md->player.x;
	ray.origin.y = md->player.y;
	return (ray);
}	

t_dda init_dda(t_coord player)
{
	t_dda dda;

	dda.delta_x = 0;
	dda.delta_y = 0;
	dda.map_x = (int)player.x;
	dda.map_y = (int)player.y;
	dda.side = 0;
	dda.side_dist_x = 0;
	dda.side_dist_y = 0;
	dda.step_x = 1;
	dda.step_y = 1;
	return (dda);
}	

void	get_deltas(t_ray ray,  t_dda *dda)
{
	dda->delta_x = DBL_MAX;
	if (ray.dir.x)
		dda->delta_x = fabs(1 / ray.dir.x);
	dda->delta_y = DBL_MAX;
	if (ray.dir.y)
		dda->delta_y = fabs(1 / ray.dir.y);
	if (ray.dir.x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (ray.origin.x - dda->map_x) * dda->delta_x;
	}
	else
		dda->side_dist_x = (dda->map_x + 1 - ray.origin.x) * dda->delta_x;
	if (ray.dir.y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (ray.origin.y - dda->map_y) * dda->delta_y;
	}
	else
		dda->side_dist_y = (dda->map_y + 1 - ray.origin.y) * dda->delta_y;
}

void	perform_dda(t_dda *dda, char **map)
{
	int hit = 0;

	while (hit == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (map[dda->map_y][dda->map_x] != '0')
			hit = 1;
	}
}

void	draw_frame(t_map *md)
{
	t_ray	ray_vect;
	t_dda	dda;
	double	dist_to_wall;
	int line_h;
	int x = -1;

	while (++x < screenWidth)
	{
		ray_vect = init_ray(md, x);
		dda = init_dda(md->player);
		get_deltas(ray_vect, &dda);
		perform_dda(&dda, md->map);
		if (dda.side == 0)
			dist_to_wall = dda.side_dist_x - dda.delta_x;
		else
			dist_to_wall = dda.side_dist_y - dda.delta_y;
		if (dist_to_wall < 1)
			line_h = screenHeight;
		else
			line_h = (int)(screenHeight / dist_to_wall);
		draw_line(md, x, line_h, dda.side);
	}
}
