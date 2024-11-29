/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleonora <eleonora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:41:22 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/27 12:44:35 by eleonora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coord	rotate_vector(t_coord src, double angle)
{
	t_coord	res;

	res.x = src.x * cos(angle) - src.y * sin(angle);
	res.y = src.x * sin(angle) + src.y * cos(angle);
	return (res);
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

	data = ft_calloc (1, sizeof(t_data));
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, SCRNWIDTH, SCRNHEIGHT, "cub3D");
	data->img = new_img(data);
	data->player.x = 0;
	data->player.y = 0;
	data->txt = ft_calloc(4, sizeof(t_img_data *));
	data->redraw = 0;
	data->num_drs = 0;
	data->can_open = NULL;
	data->frames = 0;
	return (data);
}

t_img_data	*new_img(t_data *data)
{
	t_img_data	*img_data;

	img_data = ft_calloc(1, sizeof(t_img_data));
	if (!img_data)
		clean_exit(1, "Failed to malloc", data);
	img_data->mlx_img = mlx_new_image(data->mlx, SCRNWIDTH, SCRNHEIGHT);
	img_data->img_addr = mlx_get_data_addr(img_data->mlx_img, &(img_data->bpp),
			&(img_data->img_line_len), &(img_data->img_endian));
	return (img_data);
}
