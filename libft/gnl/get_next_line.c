/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:36:20 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/29 13:41:47 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*f_r(char *return_value, char **str1, char **str2)
{
	if (str1)
	{
		free(*str1);
		*str1 = NULL;
	}
	if (str2)
	{
		free(*str2);
		*str2 = NULL;
	}
	return (return_value);
}

char	*intialise(int *end_ind, int *res_size)
{
	char	*result;

	*end_ind = 0;
	*res_size = BUFFER_SIZE + 1;
	result = (char *)gnl_calloc(*res_size, 1);
	return (result);
}

char	*read_loop(int fd, char *buf, int *b_read, char **tail)
{
	int		end_ind;
	int		res_size;
	char	*result;

	result = intialise(&end_ind, &res_size);
	if (!result)
		return (f_r(NULL, &result, &buf));
	if (gnl_check_line(buf) == -1)
	{
		gnl_strjoin(&result, buf, &end_ind, &res_size);
		*b_read = read(fd, buf, BUFFER_SIZE);
		while ((*b_read == BUFFER_SIZE) && (gnl_check_line(buf) == -1))
		{
			buf[*b_read] = '\0';
			gnl_strjoin(&result, buf, &end_ind, &res_size);
			*b_read = read(fd, buf, BUFFER_SIZE);
		}
		if (*b_read == -1)
			return (f_r(NULL, &result, &buf));
		buf[*b_read] = '\0';
	}
	last_line(buf, tail);
	gnl_strjoin(&result, buf, &end_ind, &res_size);
	free(buf);
	return (result);
}

void	last_line(char *buf, char **tail)
{
	int	ind;
	int	ind_tail;

	ind = gnl_check_line(buf);
	if (ind == -1)
	{
		f_r(NULL, tail, NULL);
		return ;
	}
	ind_tail = gnl_memcpy(*tail, &buf[ind + 1]);
	tail[0][ind_tail] = '\0';
	if (**tail == '\0')
		f_r(NULL, tail, NULL);
	buf [ind + 1] = '\0';
}

char	*get_next_line(int fd)
{
	static char	*tail;
	char		*buf;
	int			b_read;
	char		*result;

	if (fd == -1)
		return (NULL);
	b_read = 0;
	buf = gnl_calloc(BUFFER_SIZE + 1, 1);
	if (!buf)
		return (NULL);
	if (!tail)
	{
		tail = gnl_calloc(BUFFER_SIZE + 1, 1);
		b_read = read(fd, buf, BUFFER_SIZE);
		if (b_read <= 0 || !tail)
			return (f_r(NULL, &tail, &buf));
	}
	else
		b_read = gnl_memcpy(buf, tail);
	buf[b_read] = '\0';
	result = read_loop(fd, buf, &b_read, &tail);
	if (result == NULL)
		f_r(NULL, &tail, NULL);
	return (result);
}
