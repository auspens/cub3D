/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:01:38 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/27 15:50:21 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	draw_line(t_data *md, int x, int height, t_sides side)
// {
// 	int	y;
// 	int	color;
// 	int	line_lowest_p;
// 	int line_highest_p;

// 	if (side)
// 		color = 0xFF0000FF;
// 	else
// 		color = 0x00FF00FF;
// 	line_lowest_p = SCRNHEIGHT / 2 - height / 2;
// 	line_highest_p = SCRNHEIGHT / 2 + height / 2;
// 	y = line_lowest_p;
// 	while (y < line_highest_p + 1)
// 	{
// 		mlx_put_pixel(md->img, x, y, color);
// 		y++;
// 	}
// }

void	draw_line_to_img(t_data *data, t_sides side, int x, int height)
{
	int	y;
	int	line_lowest_p;
	int	line_highest_p;

	(void)side;
	y = -1;
	line_lowest_p = SCRNHEIGHT / 2 - height / 2;
	line_highest_p = SCRNHEIGHT / 2 + height / 2;
	while (++y < SCRNHEIGHT)
	{
		if (y < line_highest_p)
			my_pixel_put(data->img, x, y, data->color_ceiling);
		else if (y < line_lowest_p)
			my_pixel_put(data->img, x, y, gen_trgb(255, 255, 0, 120));
			// get_txt_color(data->img, x, y, get_txt_color(data, side, x, y));
		else
			my_pixel_put(data->img, x, y, data->color_floor);
	}
}
