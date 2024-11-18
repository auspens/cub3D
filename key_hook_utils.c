/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:12:31 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/18 14:40:34 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		print_binary_char(unsigned char c)
{
	for (int i = 7; i >= 0; i--) {
		printf("%d", (c >> i) & 1);
	}
	printf("\n");
}

void	set_key_flag(t_data *data, char key)
{
	data->key_flag |= (1 << key);
	printf("Key flag is set, flag value: ");
	print_binary_char(data->key_flag);
}

void	unset_key_flag(t_data *data, char key)
{
	data->key_flag &= ~(1 << key);
	printf("Key flag is UNset, flag value: ");
	print_binary_char(data->key_flag);
}

char	key_is_pressed(char key_flag, char key)
{
	return (key_flag & (1 << key));
}
