/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:51:01 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/25 15:44:55 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	redraw(void *data_passed)
{
	t_data			*data;
	struct timeval	time;

	data = data_passed;
	gettimeofday(&time, 0);
	data->elapsed = (time.tv_sec - data->oldtime.tv_sec) + \
				(time.tv_usec - data->oldtime.tv_usec) / (double)1000000;
	data->oldtime = time;
	iter_doors(data);
	if (data->redraw || data->sprite)
	{
		draw_frame(data);
		draw_minimap(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->img->mlx_img, 0, 0);
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->m_map.mlx_img, 0, 0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		fd;

	fd = 0;
	if (argc != 1)
		fd = open_mapfile(argv[1]);
	else
		clean_exit(1, "Erorr: incorrect number of arguments\n", NULL);
	data = init_data();
	get_input(data, fd, 100);
	close(fd);
	check_valid_map(data);
	draw_frame(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->mlx_img, 0, 0);
	init_minimap(data);
	mlx_mouse_move(data->mlx, data->mlx_win, SCRNWIDTH / 2, SCRNHEIGHT / 2);
	mlx_mouse_hide(data->mlx, data->mlx_win);
	set_hooks(data);
	mlx_loop_hook(data->mlx, &redraw, (void *)data);
	mlx_loop(data->mlx);
}
