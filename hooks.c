/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleonora <eleonora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:49:20 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/04 15:28:22 by eleonora         ###   ########.fr       */
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

void	step_forward(t_data *data, t_coord dir)
{
	if (data->map[(int)data->player.y][(int)data->player.x + (int)dir.x] == '0')
		data->player.x += dir.x;
	if (data->map[(int)data->player.y + (int)dir.y][(int)data->player.x] == '0')
		data->player.y += dir.y;
}

void	step_backward(t_data *data, t_coord dir)
{
	if (data->map[(int)data->player.y][(int)data->player.x - (int)dir.x] == '0')
		data->player.x -= dir.x;
	if (data->map[(int)data->player.y - (int)dir.y][(int)data->player.x] == '0')
		data->player.y -= dir.y;
}

void	move_player(t_data *data, int key)
{
	t_coord	step;
	//double	dist;

	if (key == XK_w)
		step = data->dir;
	else if (key == XK_s)
		step = rotate_vector(data->dir, PI);
	else if (key == XK_a)
		step = rotate_vector(data->dir, -PI / 2);
	else if (key == XK_d)
		step = rotate_vector(data->dir, PI / 2);
	//dist = 0.5 / data->frames_ps; 
	//step.x *= dist;
	//step.y *= dist;
	if (data->map[(int)data->player.y][(int)(data->player.x + step.x)] == '0')
		data->player.x += step.x;
	if (data->map[(int)(data->player.y + step.y)][(int)data->player.x] == '0')
		data->player.y += step.y;
}

int	key_press(int key, void *data_passed)
{
	t_data	*data;

	data = data_passed;
	if (key == XK_Escape)
		win_close(data);
	if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
	{
		move_player(data, key);
		draw_frame(data);
		mlx_put_image_to_window
		(data->mlx, data->mlx_win, data->img->mlx_img, 0, 0);
	}
	return (0);
}

void	set_hooks(t_data *data)
{
	mlx_key_hook(data->mlx_win, key_press, (void *)data);
	mlx_hook(data->mlx_win, 17, 1L << 17, win_close, (void *)data);
	// mlx_mouse_hook(win->win_ptr, mouse_scroll, (void *)img);
	
}

