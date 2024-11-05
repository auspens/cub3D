/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:49:20 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/05 16:57:28 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	win_close(void *data_passed)
{
	t_data	*data;

	data = data_passed;
	clean_exit(0, "ESC button pressed, closing window\n", data);
	return (0);
}

int	key_press(int key, void *data_passed)
{
	t_data	*data;

	data = data_passed;
	if (key == XK_Escape)
		win_close(data);
	if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
		move_player(data, key);
	if (key == XK_Right || key == XK_Left)
		rotate_player(data, key);
	draw_frame(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->mlx_img, 0, 0);
	return (0);
}

int	mouse_move(int x, int y, void *data_passed)
{
	t_data	*data;
	double	angle;

	(void)y;
	data = data_passed;
	if (x == SCRNWIDTH / 2)
		return (0);
	// if (x <= 5)
	// {
	// 	data->mouse_x = x;
	// 	return (key_press(XK_Left, data));
	// }
	// while (x >= SCRNWIDTH - 5)
	// {
	// 	data->mouse_x = x;
	// 	return (key_press(XK_Right, data));
	// }
	angle = ((double)(x - SCRNWIDTH / 2) / (double)SCRNWIDTH) * PI;
	data->dir = rotate_vector(data->dir, angle);
	data->plane = rotate_vector(data->plane, angle);
	draw_frame(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->mlx_img, 0, 0);
	mlx_mouse_move(data->mlx, data->mlx_win, SCRNWIDTH / 2, SCRNHEIGHT / 2);
	return (0);
}

// int	enter_window(void *data_passed)
// {
// 	t_data	*data;

// 	data = data_passed;
// 	mlx_mouse_get_pos(data->mlx, data->mlx_win,
// 		&(data->mouse_x), &(data->mouse_y));
// 	return (0);
// }

void	set_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, 17, 1L << 17, win_close, (void *)data);
	mlx_hook(data->mlx_win, 02, 1L << 0, key_press, (void *)data);
	mlx_hook(data->mlx_win, 06, 1L << 6, mouse_move, (void *)data);
	// mlx_hook(data->mlx_win, 07, 1L << 4, enter_window, (void *)data);
}

