/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:26:05 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/25 15:45:18 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	handle_sprite(t_data *data)
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

