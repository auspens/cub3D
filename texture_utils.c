/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:45:41 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/27 15:54:04 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_txt_color(t_img_data img, t_sides side, int x, int y)
{
	(void)img;
	(void)x;
	(void)y;
	if (side == NORTH)
		return (gen_trgb(255, 27, 215, 196));
	if (side == SOUTH)
		return (gen_trgb(255, 255, 171, 0));
	if (side == EAST)
		return (gen_trgb(255, 211, 102, 250));
	return (gen_trgb(255, 33, 222, 146));
}

/*this is to be updated to take parameters from provided map*/
t_img_data	*get_texture(char *addr, t_data *data)
{
	t_img_data	*img_data;

	img_data = ft_calloc(1, sizeof(t_img_data *));
	if (!img_data)
		clean_exit(1, "Failed to malloc", data);
	img_data->mlx_img = mlx_xpm_file_to_image
		(data->mlx, addr, &(img_data->width), &(img_data->height));
	if (!img_data->mlx_img)
	{
		free(img_data);
		clean_exit(1, "Failed to open texture\n", data);
	}
	return (img_data);
}
