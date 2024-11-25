/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:58:02 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/25 14:18:04 by auspensk         ###   ########.fr       */
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

void	destroy_texture(t_data *data, t_img_data *txt)
{
	mlx_destroy_image(data->mlx, txt->mlx_img);
	free(txt);
}

void	free_txt(t_data *data)
{
	if (data->txt->e)
		destroy_texture(data, data->txt->e);
	if (data->txt->s)
		destroy_texture(data, data->txt->s);
	if (data->txt->n)
		destroy_texture(data, data->txt->n);
	if (data->txt->w)
		destroy_texture(data, data->txt->w);
	if (data->txt->dr)
		destroy_texture(data, data->txt->dr);
	free(data->txt);
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	if (data->map)
		free_array(data->map);
	if (data->txt)
		free_txt(data);
	mlx_destroy_image(data->mlx, data->img->mlx_img);
	free (data->img);
	mlx_destroy_image(data->mlx, data->m_map.mlx_img);
	while (data->doors[++i].sprite.t)
	{
		mlx_destroy_image(data->mlx, data->doors[i].sprite.t->mlx_img);
		free(data->doors[i].sprite.t);
	}
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	clean_exit(int code, char *msg, t_data *data)
{
	if (msg)
		write (2, msg, ft_strlen(msg));
	if (data)
		free_data(data);
	free (data);
	exit (code);
}

