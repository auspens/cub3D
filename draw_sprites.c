/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:11:49 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/19 17:39:33 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprite(t_data *data)
{
	int	stripe;
	int	tex_x;
	int	tex_y;
	int	d;
	int	y;

	data->sprite.rel.x = data->sprite.coord.x - data->player.x;
	data->sprite.rel.y = data->sprite.coord.y - data->player.y;
	data->sprite.inv_det = 1.0 / (data->plane.x * data->dir.y
			- data->dir.x * data->plane.y);
	data->sprite.trans.x = data->sprite.inv_det * (data->dir.y
			* data->sprite.rel.x - data->dir.x * data->sprite.rel.y);
	data->sprite.trans.y = data->sprite.inv_det * (-data->plane.y
			* data->sprite.rel.x + data->plane.x * data->sprite.rel.y);
	data->sprite.sprite_scr_x = (int)((SCRNWIDTH / 2)
			* (1 + data->sprite.trans.x / data->sprite.trans.y));
	data->sprite.sprite_h = abs((int)(SCRNHEIGHT / data->sprite.trans.y)) / 3;
	data->sprite.draw_start_y = -data->sprite.sprite_h / 2 + SCRNHEIGHT / 2;
	if (data->sprite.draw_start_y < 0)
		data->sprite.draw_start_y = 0;
	data->sprite.draw_end_y = data->sprite.sprite_h / 2 + SCRNHEIGHT / 2;
	if (data->sprite.draw_end_y >= SCRNHEIGHT)
		data->sprite.draw_end_y = SCRNHEIGHT - 1;
	data->sprite.sprite_w = abs((int)(SCRNWIDTH / data->sprite.trans.y)) / 3;
	data->sprite.draw_start_x = -data->sprite.sprite_w / 2 + data->sprite.sprite_scr_x;
	if (data->sprite.draw_start_x < 0)
		data->sprite.draw_start_x = 0;
	data->sprite.draw_end_x = data->sprite.sprite_w / 2 + data->sprite.sprite_scr_x;
	if (data->sprite.draw_end_x >= SCRNWIDTH)
		data->sprite.draw_end_x = SCRNWIDTH - 1;
	stripe = data->sprite.draw_start_x;
	while (stripe < data->sprite.draw_end_x)
	{
		tex_x = (int)(stripe - (-data->sprite.sprite_w / 2 + data->sprite.sprite_scr_x)) * data->sprite.txtr->width / data->sprite.sprite_w;
		if (data->sprite.trans.y > 0 && stripe > 0 && stripe < SCRNWIDTH && data->sprite.trans.y < data->z_buf[stripe])
		{
			y = data->sprite.draw_start_y;
			while (y < data->sprite.draw_end_y)
			{
				d = y * 256 - SCRNHEIGHT * 128 + data->sprite.sprite_h * 128;
				tex_y = ((d * data->sprite.txtr->height) / data->sprite.sprite_h) / 256;
				data->sprite.color = my_pixel_get(data->sprite.txtr, tex_x, tex_y);
				// if ((data->sprite.color >> 24) != 0xFF)
				// 	my_pixel_put(data->img, stripe, y, data->sprite.color);
				if ((data->sprite.color & 0x00FFFFFF) != 0)
					my_pixel_put(data->img, stripe, y, data->sprite.color);
				y++;
			}
		}
		stripe ++;
	}
}
