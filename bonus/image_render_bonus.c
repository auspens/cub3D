/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:01:38 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/29 12:21:29 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	calc_wall_txtr_x(t_dda dda, t_draw_data *draw, t_data *data, t_ray ray)
{
	if (!draw || !data)
		return ;
	if (dda.side == WEST)
		draw->txtr = data->txt->w;
	else if (dda.side == EAST)
		draw->txtr = data->txt->e;
	else if (dda.side == NORTH)
		draw->txtr = data->txt->n;
	else if (dda.side == SOUTH)
		draw->txtr = data->txt->s;
	if (dda.hit == 'D')
		draw->txtr = data->doors[0].txtr;
	if (!draw->txtr)
		return ;
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

void	calc_line_height(t_dda dda, t_draw_data *draw_data)
{
	if (dda.side == WEST || dda.side == EAST)
		draw_data->per_wall_dist = dda.side_dist_x - dda.delta_x;
	else
		draw_data->per_wall_dist = dda.side_dist_y - dda.delta_y;
	draw_data->line_height = (int)(SCRNHEIGHT / draw_data->per_wall_dist);
}

void	draw_line_to_img(t_data *data, int x, t_draw_data *draw, int y)
{
	int	line_lowest_p;
	int	line_highest_p;
	int	color;

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

