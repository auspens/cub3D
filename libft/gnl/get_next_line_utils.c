/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:36:15 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/29 13:40:49 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	gnl_check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	gnl_strjoin(char **dest, char *src, int *ind, int *res_size)
{
	if ((*res_size - *ind) < BUFFER_SIZE + 1)
		*dest = gnl_realloc(*dest, res_size);
	if (*dest == NULL)
		return ;
	*ind += gnl_memcpy(&(dest[0][*ind]), src);
	dest[0][*ind] = '\0';
}

int	gnl_memcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	return (i);
}

char	*gnl_realloc(char *res, int *res_size)
{
	char	*new_res;
	char	*old_res;
	int		ind;

	old_res = res;
	*res_size = *res_size * 2;
	new_res = gnl_calloc(*res_size, 1);
	if (new_res == NULL)
		return (NULL);
	ind = gnl_memcpy(new_res, res);
	new_res[ind] = '\0';
	res = new_res;
	free(old_res);
	return (res);
}

char	*gnl_calloc(int size, int num)
{
	char	*res;
	size_t	total;

	total = num * size;
	res = malloc(total);
	if (res == 0)
		return (0);
	while (total > 0)
	{
		res[total - 1] = 0;
		total --;
	}
	return (res);
}
