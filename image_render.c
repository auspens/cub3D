/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:01:38 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/25 11:35:36 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_addr + (y * data->img_line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_pixel_get(t_img_data *img, int x, int y)
{
	char	*dst;

	dst = img->img_addr + (y * img->img_line_len + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

int check_door_state(t_draw_data *draw, t_door *door, t_sides side)
{
	if (door->state == 2) //open
		return (1);
	if (door->state == 0) //closed
		return (0);
	if (side == NORTH || side == EAST)
	{
		if (draw->wall_x > 1 - door->open_ratio) //openinig or closing
 			return (1);
	}
	else
	{
		if (draw->wall_x < door->open_ratio)
			return (1);
	}
	return (0);
}
float	dist_to_door(t_coord player, t_dda dda)
{
	float dist;

	if (dda.side == EAST || dda.side == WEST)
		dist = fabs(player.x - dda.map_x);
	else
		dist = fabs(player.y - dda.map_y);
	return (dist);
}

void	handle_door(t_dda dda, t_draw_data *draw, t_data *data, t_ray ray)
{
	int can_see_further;

	int i = -1;
	t_door *door = NULL;
	while (++i < 24 && data->doors[i].x)
	{
		if (data->doors[i].x == dda.map_x)
		{
			if (data->doors[i].y == dda.map_y)
				door = &data->doors[i];
		}
	}
	if (door && door->state)
		data->sprite = &door->sprite;
	can_see_further = check_door_state(draw, door, dda.side);
	if (can_see_further)
	{
		dda.hit = 0;
		perform_dda(&dda, data->map);
		calc_line_height(dda, draw);
		calc_wall_txtr_x(dda, draw, data, ray);
		return ;
	}
	if (door->state == 1 || door->state == 3)
	{
		//if (dda.side == NORTH || dda.side == EAST)
		draw->txtr_x += door->open_ratio * (double)draw->txtr->width;
	}
	else if (door->state == 0 && dist_to_door(data->player, dda) < 2.5)
		data->can_open = door;
}


void	calc_wall_txtr_x(t_dda dda, t_draw_data *draw, t_data *data, t_ray ray)
{
	if (dda.side == WEST)
		draw->txtr = data->txt->w;
	else if (dda.side == EAST)
		draw->txtr = data->txt->e;
	else if (dda.side == NORTH)
		draw->txtr = data->txt->n;
	else if (dda.side == SOUTH)
		draw->txtr = data->txt->s;
	if (dda.hit == 'D')
		draw->txtr = data->txt->dr;
	if (dda.side == WEST || dda.side == EAST)
		draw->wall_x = data->player.y + draw->per_wall_dist * ray.dir.y;
	else
		draw->wall_x = data->player.x + draw->per_wall_dist * ray.dir.x;
	draw->wall_x -= (int)draw->wall_x;
	draw->txtr_x = (int)(draw->wall_x * draw->txtr->width);
	if (dda.side == SOUTH || dda.side == WEST)
		draw->txtr_x = draw->txtr->width - draw->txtr_x - 1;
	if (dda.hit == 'D')
		handle_door(dda, draw, data, ray);
}


void	draw_line_to_img(t_data *data, int x, t_draw_data *draw)
{
	int	y;
	int	line_lowest_p;
	int	line_highest_p;
	int	color;

	y = -1;
	line_highest_p = SCRNHEIGHT / 2 - draw->line_height / 2;
	line_lowest_p = SCRNHEIGHT / 2 + draw->line_height / 2;
	draw->step = (double)draw->txtr->height / draw->line_height;
	if (line_highest_p < 0)
		draw->txtr_pos = -line_highest_p * draw->step;
	else
		draw->txtr_pos = 0;
	while (++y < SCRNHEIGHT)
	{
		if (y < line_highest_p)
			my_pixel_put(data->img, x, y, data->color_ceiling);
		if (y >= line_highest_p && y <= line_lowest_p)
		{
			draw->txtr_y = (int)draw->txtr_pos & (draw->txtr->height - 1);
			draw->txtr_pos += draw->step;
			color = my_pixel_get(draw->txtr, draw->txtr_x, draw->txtr_y);
			my_pixel_put(data->img, x, y, color);
		}
		if (y > line_lowest_p)
			my_pixel_put(data->img, x, y, data->color_floor);
	}
}

