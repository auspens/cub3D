/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:26:05 by auspensk          #+#    #+#             */
/*   Updated: 2024/12/02 11:25:33 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_sprite(double d, t_draw_sprite draw, t_sprite sp, t_data *data)
{
	int				x;
	int				y;
	int				text_x;
	int				text_y;
	unsigned int	color;

	x = draw.start_x - 1;
	while (++x < draw.end_x)
	{
		text_x = (x - draw.start_x) * sp.size / draw.sprite_side;
		if (draw.move)
			text_x += draw.move * sp.size;
		if (d < data->buffer[x])
		{
			y = draw.start_y - 1;
			while (++y < draw.end_y)
			{
				text_y = (y - draw.start_y) * sp.size / draw.sprite_side;
				color = my_pixel_get(sp.t, text_x, text_y);
				if ((color & 0x00FFFFFF) != 0)
					my_pixel_put(data->img, x, y, color);
			}
		}
	}
}

t_coord	calc_trpos_vect(t_sprite sprite, t_data *data)
{
	t_coord			trpos;
	t_coord			relpos;
	double			invdet;

	relpos.x = sprite.pos.x - data->player.x;
	relpos.y = sprite.pos.y - data->player.y;
	invdet = 1.0 / (data->plane.x * data->dir.y - data->dir.x * data->plane.y);
	trpos.x = invdet * (data->dir.y * relpos.x - data->dir.x * relpos.y);
	trpos.y = invdet * (-data->plane.y * relpos.x + data->plane.x * relpos.y);
	return (trpos);
}

void	calc_start_end(t_draw_sprite *draw)
{
	draw->start_x = draw->sprite_scr_x - draw->sprite_side / 2;
	if (draw->start_x < 0)
		draw->start_x = 0;
	draw->end_x = draw->sprite_scr_x + draw->sprite_side / 2;
	if (draw->end_x >= SCRNWIDTH)
		draw->end_x = SCRNWIDTH - 1;
	draw->start_y = SCRNHEIGHT / 2 - draw->sprite_side / 2 + draw->fl_offset;
	if (draw->start_y < 0)
		draw->start_y = 0;
	draw->end_y = SCRNHEIGHT / 2 + draw->sprite_side / 2 + draw->fl_offset;
	if (draw->end_y >= SCRNHEIGHT)
		draw->end_y = SCRNHEIGHT - 1;
}

void	handle_sprite(t_data *data)
{
	t_coord			trpos; 
	t_sprite		sprite;
	t_draw_sprite	draw;

	if (!data->sprite)
		return ;
	sprite = *data->sprite;
	trpos = calc_trpos_vect(sprite, data);
	if (trpos.y <= 0)
		return ;
	draw.sprite_scr_x = (int)((SCRNWIDTH / 2) * (1 + trpos.x / trpos.y));
	draw.sprite_side = (int)(SCRNHEIGHT / (trpos.y)) / sprite.scale;
	draw.fl_offset = (int)((SCRNHEIGHT / (trpos.y)) * \
						(1 - 1.0 / sprite.scale) / 2);
	if (!sprite.moves)
		draw.move = 0;
	else
		draw.move = (data->oldtime.tv_sec * 4 + \
						data->oldtime.tv_usec / 250000) % sprite.moves;
	calc_start_end(&draw);
	draw_sprite(trpos.y, draw, sprite, data);
}
