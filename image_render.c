/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:01:38 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/28 13:57:13 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_to_img(t_data *data, t_sides side, int x, int height)
{
	int	y;
	int	line_lowest_p;
	int	line_highest_p;
	int	color;

/*this is temp before the textures are set*/
	if (side == EAST)
		color = 0xFF0000FF;
	else if (side == WEST)
		color = gen_trgb(255, 167, 226, 29);
	else if (side == NORTH)
		color = gen_trgb (255, 226, 128, 29);
	else
		color = gen_trgb(255, 88, 29, 226);
/*this is temp before the textures are set*/
	y = -1;
	line_highest_p = SCRNHEIGHT / 2 - height / 2;
	line_lowest_p = SCRNHEIGHT / 2 + height / 2;
	while (++y < SCRNHEIGHT)
	{
		if (y < line_highest_p)
			my_pixel_put(data->img, x, y, data->color_ceiling);
		if (y > line_highest_p && y < line_lowest_p)
			my_pixel_put(data->img, x, y, color);
			// get_txt_color(data->img, x, y, get_txt_color(data, side, x, y));
		if (y > line_lowest_p)
			my_pixel_put(data->img, x, y, data->color_floor);
	}
}
