/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:58:02 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/28 15:05:36 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map)
{
	int	idx;

	idx = 0;
	if (!map)
		return ;
	while (map[idx])
		free(map[idx++]);
	free(map);
}

void	free_data(t_data *data)
{
	if (data->map)
		free_map(data->map);
	mlx_destroy_image(data->mlx, data->img->mlx_img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	/* free and close the rest*/
}

void	clean_exit(int code, char *msg, t_data *data)
{
	if (msg)
		write (2, msg, ft_strlen(msg));
	if (data)
		free_data(data);
	exit (code);
}
