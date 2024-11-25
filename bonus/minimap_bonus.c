/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:52:10 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/25 15:45:07 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	calculate_map_borders(int *x, int *y, t_data *data)
{
	int	x_max;

	x_max = 0;
	*y = 0;
	while (data->map[*y])
	{
		*x = 0;
		while (data->map[*y][*x] != '\n')
			(*x)++;
		if (*x > x_max)
			x_max = *x;
		(*y)++;
	}
	*x = x_max;
}

void	define_mmap_size(t_data *data)
{
	int	x;
	int	y;

	calculate_map_borders(&x, &y, data);
	if (y > x)
	{
		data->m_map.height = SCRNHEIGHT / 4;
		data->m_map.scale = data->m_map.height / y;
		data->m_map.height = y * data->m_map.scale;
		data->m_map.width = x * data->m_map.scale;
	}
	else
	{
		data->m_map.width = SCRNWIDTH / 4;
		data->m_map.scale = data->m_map.width / x;
		data->m_map.width = x * data->m_map.scale;
		data->m_map.height = y * data->m_map.scale;
	}
}

void	draw_player(t_data *data)
{
	int		x;
	int		y;
	int		i;
	int		j;

	i = 0;
	j = 0;
	y = data->player.y * data->m_map.scale;
	while (++i < 4)
	{
		x = data->player.x * data->m_map.scale;
		j = 0;
		while (++j < 4)
		{
			my_pixel_put(&(data->m_map), x, y, data->m_map_colors.p);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_data *data)
{
	t_coord	coord;
	int		scaled_x;
	int		scaled_y;
	char	nl;

	coord.y = -1;
	while (++coord.y < data->m_map.height)
	{
		coord.x = -1;
		nl = 0;
		while (++coord.x < data->m_map.width)
		{
			scaled_x = coord.x / data->m_map.scale;
			scaled_y = coord.y / data->m_map.scale;
			if (nl)
				my_pixel_put(&(data->m_map), coord.x, coord.y,
					data->m_map_colors.w);
			else
				check_char_and_draw(coord, data, &nl,
					data->map[scaled_y][scaled_x]);
		}
	}
	draw_player(data);
}

void	init_minimap(t_data *data)
{
	define_mmap_size(data);
	data->m_map_colors.s = gen_trgb(120, 76, 133, 100);
	data->m_map_colors.w = gen_trgb(120, 54, 64, 136);
	data->m_map_colors.d = gen_trgb(120, 225, 163, 75);
	data->m_map_colors.p = gen_trgb(120, 181, 64, 60);
	data->m_map.mlx_img = mlx_new_image
		(data->mlx, data->m_map.width, data->m_map.height);
	data->m_map.img_addr = mlx_get_data_addr
		(data->m_map.mlx_img, &(data->m_map.bpp),
			&(data->m_map.img_line_len), &(data->m_map.img_endian));
	draw_minimap(data);
	mlx_put_image_to_window
		(data->mlx, data->mlx_win, data->m_map.mlx_img, 0, 0);
}
