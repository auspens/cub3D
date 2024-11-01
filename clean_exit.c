/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:58:02 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/01 14:23:41 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **array)
{
	int	idx;

	idx = 0;
	if (!array)
		return ;
	while (array[idx])
		free(array[idx++]);
	free(array);
}

void	free_data(t_data *data)
{
	if (data->map)
		free_array(data->map);
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

void	exit_at_reading_input(t_data *data, int fd, char **arr, char *msg)
{
	free_array(arr);
	close(fd);
	clean_exit(1, msg, data);
}
