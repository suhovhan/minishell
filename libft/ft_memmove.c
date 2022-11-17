/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 03:27:42 by suhovhan          #+#    #+#             */
/*   Updated: 2022/04/21 14:46:33 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*dest2;
	unsigned const char	*src2;
	size_t				i;

	dest2 = dest;
	src2 = src;
	if (!dest && !src)
		return (0);
	if (dest2 >= src2)
	{
		while (len--)
			dest2[len] = src2[len];
	}
	else if (dest2 < src2)
	{
		i = 0;
		while (i < len)
		{
			dest2[i] = src2[i];
			i++;
		}
	}
	return (dest);
}
