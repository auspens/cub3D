/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:51:01 by auspensk          #+#    #+#             */
/*   Updated: 2024/10/27 15:59:30 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mlx_loop(data->mlx);
}
