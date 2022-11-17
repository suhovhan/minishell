/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:56:37 by suhovhan          #+#    #+#             */
/*   Updated: 2022/04/26 12:35:18 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t len)
{
	int		total;
	size_t	i;
	size_t	j;
	size_t	ldest;
	size_t	lsrc;

	i = 0;
	j = 0;
	ldest = ft_strlen(dest);
	lsrc = ft_strlen((char *)src);
	if (len > ldest)
		total = ldest + lsrc;
	else
		total = lsrc + len;
	j = ldest;
	while (src[i] && j + 1 < len)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = 0;
	return (total);
}
