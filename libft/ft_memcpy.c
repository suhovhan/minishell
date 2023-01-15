/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 02:27:56 by suhovhan          #+#    #+#             */
/*   Updated: 2022/04/11 21:17:48 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char		*dest2;
	unsigned const char	*src2;
	size_t				i;

	dest2 = dest;
	src2 = src;
	i = 0;
	if (!dest && !src)
		return (0);
	while (i < len)
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dest);
}
