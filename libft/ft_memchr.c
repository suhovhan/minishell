/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 22:15:06 by suhovhan          #+#    #+#             */
/*   Updated: 2022/05/10 02:36:10 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int ch, size_t n)
{
	size_t			i;
	const char		*str2;

	str2 = str;
	i = 0;
	if (str2 == NULL)
		return (NULL);
	while (i < n)
	{
		if (str2[i] == (char)ch)
			return ((void *)&str2[i]);
		i++;
	}
	return (NULL);
}
