/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:41:22 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/27 14:54:00 by auspensk         ###   ########.fr       */
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

t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc (1, sizeof(t_data *));
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, SCRNWIDTH, SCRNHEIGHT, "cub3D");
	data->img = new_img(data);
	data->dir.y = -1; //temp fix, will be correctly set in check_map
	data->plane.x = 1; // temp fix, will be correctly set in check_map
	return (data);
}

t_img_data	*new_img(t_data *data)
{
	t_img_data	*img_data;

	img_data = ft_calloc(1, sizeof(t_img_data *));
	if (!img_data)
		clean_exit(1, "Failed to malloc", data);
	img_data->mlx_img = mlx_new_image(data->mlx, SCRNWIDTH, SCRNHEIGHT);
	img_data->img_addr = mlx_get_data_addr(img_data->mlx_img, &(img_data->bpp),
			&(img_data->img_line_len), &(img_data->img_endian));
	return (img_data);
}
