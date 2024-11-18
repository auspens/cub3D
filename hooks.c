/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:49:20 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/18 14:50:41 by auspensk         ###   ########.fr       */
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

// int	key_press(int key, void *data_passed)
// {
// 	t_data	*data;

// 	data = data_passed;
// 	if (key == XK_Escape)
// 		win_close(data);
// 	if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
// 		move_player(data, key);
// 	if (key == XK_Right || key == XK_Left)
// 		rotate_player(data, key);
// 	if (key == XK_space && data->door.state == 0 && data->can_open[0] == data->door.x && data->can_open[1] == data->door.y)
// 		data->door.state = 1;
// 	data->redraw = 1;
// 	return (0);
// }

int	key_press(int key, void *data_passed)
{
	t_data	*data;

	data = data_passed;
	if (key == XK_Escape)
		win_close(data);
	if (key == XK_w && !(key_is_pressed(data->key_flag, 1)))
		set_key_flag(data, 1);
	if (key == XK_a && !(key_is_pressed(data->key_flag, 2)))
		set_key_flag(data, 2);
	if (key == XK_s && !(key_is_pressed(data->key_flag, 3)))
		set_key_flag(data, 3);
	if (key == XK_d && !(key_is_pressed(data->key_flag, 4)))
		set_key_flag(data, 4);
	if (key == XK_Right && !(key_is_pressed(data->key_flag, 6)))
		set_key_flag(data, 6);
	if (key == XK_Left && !(key_is_pressed(data->key_flag, 5)))
		set_key_flag(data, 5);
	if (key == XK_space && data->door.state == 0
		&& data->can_open[0] == data->door.x
		&& data->can_open[1] == data->door.y)
		data->door.state = 1;
	data->redraw = 1;
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
	angle = ((double)(x - SCRNWIDTH / 2) / (double)SCRNWIDTH) * PI;
	data->dir = rotate_vector(data->dir, angle);
	data->plane = rotate_vector(data->plane, angle);
	data->redraw = 1;
	mlx_mouse_move(data->mlx, data->mlx_win, SCRNWIDTH / 2, SCRNHEIGHT / 2);
	return (0);
}

int	key_release(int key, void *data_passed)
{
	t_data	*data;

	data = data_passed;

	if (key == XK_w)
		unset_key_flag(data, 1);
	if (key == XK_a)
		unset_key_flag(data, 2);
	if (key == XK_s)
		unset_key_flag(data, 3);
	if (key == XK_d)
		unset_key_flag(data, 4);
	if (key == XK_Left)
		unset_key_flag(data, 5);
	if (key == XK_Right)
		unset_key_flag(data, 6);
	return (0);
}

void	set_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, 17, 1L << 17, win_close, (void *)data);
	mlx_hook(data->mlx_win, 02, 1L << 0, key_press, (void *)data);
	mlx_hook(data->mlx_win, 06, 1L << 6, mouse_move, (void *)data);
	mlx_hook(data->mlx_win, 03, 1L << 1, key_release, (void *)data);
}

