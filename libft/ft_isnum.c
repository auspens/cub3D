/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auspensk <auspensk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:16:38 by auspensk          #+#    #+#             */
/*   Updated: 2024/11/01 14:28:30 by auspensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*returns 0 if the str is null or empty or
contains chars other than between '0' and '9'*/
int	ft_isnum(char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}
