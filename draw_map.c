/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:43:36 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/25 11:49:24 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	init_ray(t_data *md, int x)
{
	t_ray	ray;
	double	rel_pos;

	rel_pos = 2 * x / (double)SCRNWIDTH - 1;
	ray.dir.x = md->dir.x + md->plane.x * rel_pos;
	ray.dir.y = md->dir.y + md->plane.y * rel_pos;
	ray.origin.x = md->player.x;
	ray.origin.y = md->player.y;
	return (ray);
}

t_dda	init_dda(t_coord player)
{
	t_dda	dda;

	dda.delta_x = 0;
	dda.delta_y = 0;
	dda.map_x = (int)player.x;
	dda.map_y = (int)player.y;
	dda.side = 0;
	dda.side_dist_x = 0;
	dda.side_dist_y = 0;
	dda.step_x = 1;
	dda.step_y = 1;
	dda.hit = 0;
	return (dda);
}

void	get_deltas(t_ray ray, t_dda *dda)
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
	while (dda->hit == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_x;
			dda->map_x += dda->step_x;
			if (dda->step_x == -1)
				dda->side = WEST;
			else
				dda->side = EAST;
		}
		else
		{
			dda->side_dist_y += dda->delta_y;
			dda->map_y += dda->step_y;
			if (dda->step_y == -1)
				dda->side = NORTH;
			else
				dda->side = SOUTH;
		}
		if (map[dda->map_y][dda->map_x] != '0')
			dda->hit = map[dda->map_y][dda->map_x];
	}
}

void	calc_line_height(t_dda dda, t_draw_data *draw_data)
{
	if (dda.side == WEST || dda.side == EAST)
		draw_data->per_wall_dist = dda.side_dist_x - dda.delta_x;
	else
		draw_data->per_wall_dist = dda.side_dist_y - dda.delta_y;
	draw_data->line_height = (int)(SCRNHEIGHT / draw_data->per_wall_dist);
}

void handle_sprite(t_data *data);

void	draw_frame(t_data *data)
{
	t_ray		ray_vect;
	t_dda		dda;
	int			x;
	t_draw_data	draw_data;

	data->can_open = NULL;
	data->sprite = NULL;
	data->redraw = 0;
	x = -1;
	while (++x < SCRNWIDTH)
	{
		ray_vect = init_ray(data, x);
		dda = init_dda(data->player);
		get_deltas(ray_vect, &dda);
		perform_dda(&dda, data->map);
		calc_line_height(dda, &draw_data);
		calc_wall_txtr_x(dda, &draw_data, data, ray_vect);
		draw_line_to_img(data, x, &draw_data);
		data->buffer[x] = draw_data.per_wall_dist;
	}
	handle_sprite(data);
}

void handle_sprite(t_data *data)
{
	if (!data->sprite)
		return ;
	t_coord relpos;
	t_coord trpos;
	t_sprite sprite = *data->sprite;
    relpos.x = sprite.pos.x - data->player.x;
    relpos.y = sprite.pos.y - data->player.y;

    double invdet = 1.0 / (data->plane.x * data->dir.y - data->dir.x * data->plane.y);
	trpos.x = invdet * (data->dir.y * relpos.x - data->dir.x * relpos.y);
    trpos.y = invdet * (-data->plane.y * relpos.x + data->plane.x * relpos.y);

    int sprite_scr_x = (int)((SCRNWIDTH / 2) * (1 + trpos.x / trpos.y));
	//printf("trpos.x ia %f, trpos.y is %f, sprite_scr_x is %i\n", trpos.x, trpos.y, sprite_scr_x);
    if (trpos.y <= 0)
		return ;

	//int scale = 4;
	int sprite_side = (int)(SCRNHEIGHT / (trpos.y)) / sprite.scale;

	int fl_offset = (int)((SCRNHEIGHT / (trpos.y)) * (1 - 1.0/sprite.scale) / 2);

	//printf("sprite side is %i and offeset to floor is %i\n", sprite_side, fl_offset);

    int drawStartY = -sprite_side / 2 + SCRNHEIGHT / 2 + fl_offset;

    if (drawStartY < 0)
		drawStartY = 0;

    int drawEndY = sprite_side / 2 + SCRNHEIGHT / 2 + fl_offset;
    if (drawEndY >= SCRNHEIGHT)
		drawEndY = SCRNHEIGHT - 1;

    int drawStartX = -sprite_side / 2 + sprite_scr_x;
    if (drawStartX < 0)
		drawStartX = 0;
    int drawEndX = sprite_side / 2 + sprite_scr_x;
    if (drawEndX >= SCRNWIDTH)
		drawEndX = SCRNWIDTH - 1;

	int move;
	if (!sprite.moves)
		move = 0;
	else
		move = (data->oldtime.tv_sec * 4 + data->oldtime.tv_usec / 250000) % sprite.moves;
	//printf("move is %i\n", move);
    for (int stripe = drawStartX; stripe < drawEndX; stripe++)
    {
    	int text_x = (int)(256 * (stripe - (-sprite_side / 2 + sprite_scr_x)) * sprite.size / sprite_side) / 256;
		if (move)
			text_x += move * sprite.size;
        if (trpos.y > 0 && trpos.y < data->buffer[stripe])
		{
        	for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        	{
			//printf("stripe is %i, y is %i\n", stripe, y);
          	int d = (y - fl_offset) * 256 - SCRNHEIGHT * 128 + sprite_side * 128; //256 and 128 factors to avoid floats
          	int text_y = ((d * sprite.size) / sprite_side) / 256;
			//printf("text_x is %i, text_y is %i\n", text_x, text_y);
          	unsigned int color = my_pixel_get(data->sprite->t, text_x, text_y);
          	if ((color & 0x00FFFFFF) != 0)
				my_pixel_put(data->img, stripe, y, color);
        	}
      	}
	}
}
