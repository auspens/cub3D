/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleonora <eleonora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:49:20 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/09 11:56:28 by eleonora         ###   ########.fr       */
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

int can_walk(t_data *data, int x, int y)
{
	char c = data->map[y][x];
	if (c == '0')
		return (1);
	if (c == 'D' && data->door.state == 2)
		return (1);
	return (0);
}

void	make_step(t_data *data, t_coord step)
{
	int y;
	int new_y;
	int x;
	int new_x;

	y = (int)data->player.y;
	new_y = (int)(data->player.y + step.y);
	x = (int)data->player.x;
	new_x = (int)(data->player.x + step.x);
	if (can_walk(data, new_x, y))
		data->player.x += step.x;
	if (can_walk(data, x, new_y))
		data->player.y += step.y;
}

void	move_player(t_data *data, int key)
{
	t_coord	step;
	double	dist;

	if (key == XK_w)
		step = data->dir;
	else if (key == XK_s)
		step = rotate_vector(data->dir, PI);
	else if (key == XK_a)
		step = rotate_vector(data->dir, -PI / 2);
	else if (key == XK_d)
		step = rotate_vector(data->dir, PI / 2);
	dist = 0.2; 
	step.x *= dist;
	step.y *= dist;
	make_step(data, step);
}

void	rotate_player(t_data *data, int key)
{
	double	angle;

	if (key == XK_Right)
		angle = 0.05 * PI;
	else 
		angle = 0.05 * -PI;
	data->dir = rotate_vector(data->dir, angle);
	data->plane = rotate_vector(data->plane, angle);
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
	if (key == XK_space && data->door.state == 0 && data->can_open[0] == data->door.x && data->can_open[1] == data->door.y)
		data->door.state = 1;
	data->redraw = 1;
	return (0);
}

void	set_hooks(t_data *data)
{
	//mlx_key_hook(data->mlx_win, open_door, (void *)data);
	mlx_hook(data->mlx_win, 17, 1L << 17, win_close, (void *)data);
	mlx_hook(data->mlx_win, 02, 1L << 0, key_press, (void *)data);
	// mlx_mouse_hook(win->win_ptr, mouse_scroll, (void *)img);
}

