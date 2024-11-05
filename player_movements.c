/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:39:30 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/05 15:41:40 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	step_forward(t_data *data, t_coord dir)
{
	if (data->map[(int)data->player.y][(int)data->player.x + (int)dir.x] == '0')
		data->player.x += dir.x;
	if (data->map[(int)data->player.y + (int)dir.y][(int)data->player.x] == '0')
		data->player.y += dir.y;
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
	dist = 5000 / data->frames_ps;
	step.x *= dist;
	step.y *= dist;
	if (data->map[(int)data->player.y][(int)(data->player.x + step.x)] == '0')
		data->player.x += step.x;
	if (data->map[(int)(data->player.y + step.y)][(int)data->player.x] == '0')
		data->player.y += step.y;
}

void	rotate_player(t_data *data, int key)
{
	double	angle;

	if (key == XK_Right)
		angle = 500 * PI / data->frames_ps;
	else
		angle = 500 * -PI / data->frames_ps;
	data->dir = rotate_vector(data->dir, angle);
	data->plane = rotate_vector(data->plane, angle);
}
