/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:58:40 by suhovhan          #+#    #+#             */
/*   Updated: 2022/04/26 12:35:56 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t len)
{
	int		res;
	size_t	i;

	i = 0;
	res = ft_strlen((char *)src);
	if (len == 0)
		return (res);
	while (i < len - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (len > i)
		dest[i] = 0;
	return (res);
}
