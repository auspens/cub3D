/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_inits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:27:49 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/29 11:28:13 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	init_ray(t_data *md, int x)
{
	t_ray	ray;
	double	rel_pos;

	rel_pos = 2 * x / (double)SCRNWIDTH - 1;
	ray.dir.x = md->dir.x + md->plane.x * rel_pos;
	ray.dir.y = md->dir.y + md->plane.y * rel_pos;
	ray.origin.x = md->player.x;
	ray.origin.y = md->player.y;
	return (ray);
}

t_dda	init_dda(t_coord player)
{
	t_dda	dda;

	dda.delta_x = 0;
	dda.delta_y = 0;
	dda.map_x = (int)player.x;
	dda.map_y = (int)player.y;
	dda.side = 0;
	dda.side_dist_x = 0;
	dda.side_dist_y = 0;
	dda.step_x = 1;
	dda.step_y = 1;
	return (dda);
}
