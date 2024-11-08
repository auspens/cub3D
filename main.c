/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleonora <eleonora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:51:01 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/08 09:14:35 by eleonora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	timer(void *data_passed)
{
	t_data	*data;
	struct timeval time;

	data = data_passed;
	gettimeofday(&time, 0);
	data->elapsed = (time.tv_sec - data->oldtime.tv_sec) + \
				(time.tv_usec - data->oldtime.tv_usec) / (double)1000000;
	data->oldtime = time;
	//printf("elapsed %lu microsec\n", elapsed);
	if (data->door.state == 1)
	{
		data->door.open_ratio += 5000 *data->elapsed;
		if (data->door.open_ratio >= 1)
		{
			data->door.open_ratio = 1;
			data->door.state = 2;
		}
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
	set_hooks(data);
	mlx_loop_hook(data->mlx, &timer, (void *)data);
	mlx_loop(data->mlx);
}
