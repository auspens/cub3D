/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:41:22 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/23 16:15:24 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_addr + (y * data->img_line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	gen_trgb(int opacity, int red, int green, int blue)
{
	if (opacity > 255 || red > 255 || green > 255 || blue > 255)
		return (0);
	return (opacity << 24 | red << 16 | green << 8 | blue);
}

/*this is to be updated to take parameters from provided map*/
int	get_color(t_sides side)
{
	if (side == CEILING)
		return (gen_trgb(255, 225, 30, 0));
	if (side == SOUTH)
		return (gen_trgb(255, 255, 120, 0));
	if (side == NORTH)
		return (gen_trgb(255, 0, 162, 255));
	if (side == EAST)
		return (gen_trgb(255, 255, 255, 0));
	if (side == WEST)
		return (gen_trgb(255, 255, 0, 255));
	if (side == FLOOR)
		return (gen_trgb(255, 0, 255, 255));
	return (gen_trgb(255, 255, 255, 255));
}

t_img_data	*new_img(t_data *data)
{
	t_img_data	*img_data;

	img_data = ft_calloc(1, sizeof(t_img_data *));
	img_data->mlx_img = mlx_new_image(data->mlx, SCRNWIDTH, SCRNHEIGHT);
	img_data->img_addr = mlx_get_data_addr(img_data->mlx_img, &(img_data->bpp),
			&(img_data->img_line_len), &(img_data->img_endian));
	return (img_data);
}
