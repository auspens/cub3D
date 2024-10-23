/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:47:07 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/23 11:52:32 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc (1, sizeof(t_data *));
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, SCRNWIDTH, SCRNHEIGHT, "cub3D");
	data->img = new_img(data);
	return (data);
}
