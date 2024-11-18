/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:58:40 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/18 12:18:05 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_char_and_draw(t_coord coord, t_data *data, char *nl, char value)
{
	if (value == '\n')
	{
		*nl = 1;
		my_pixel_put(&(data->m_map), coord.x, coord.y, data->m_map_colors.w);
	}
	else if (*nl)
		my_pixel_put(&(data->m_map), coord.x, coord.y, data->m_map_colors.w);
	else if (value == '1' || value == ' ')
		my_pixel_put(&(data->m_map), coord.x, coord.y, data->m_map_colors.w);
	else if (value == 'D')
		my_pixel_put(&(data->m_map), coord.x, coord.y, data->m_map_colors.d);
	else
		my_pixel_put(&(data->m_map), coord.x, coord.y, data->m_map_colors.s);
}
