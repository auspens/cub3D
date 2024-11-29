/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:45:41 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/29 10:31:04 by auspensk         ###   ########.fr       */
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

int	get_texture(char *addr, t_data *data, t_img_data **img_data)
{
	char	*tr_addr;

	if (*img_data)
		return (1);
	if (!addr)
		return (1);
	*img_data = ft_calloc(1, sizeof(t_img_data));
	if (!*img_data)
		clean_exit(1, "Failed to malloc", data);
	tr_addr = ft_strtrim(addr, "\n");
	(*img_data)->mlx_img = mlx_xpm_file_to_image
		(data->mlx, tr_addr, &((*img_data)->width), &((*img_data)->height));
	free(tr_addr);
	if (!(*img_data)->mlx_img)
		return (1);
	(*img_data)->img_addr = mlx_get_data_addr((*img_data)->mlx_img,
			&((*img_data)->bpp),
			&((*img_data)->img_line_len), &((*img_data)->img_endian));
	return (0);
}
