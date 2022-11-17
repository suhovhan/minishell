/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:27:38 by suhovhan          #+#    #+#             */
/*   Updated: 2022/04/06 01:50:45 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str2 = str;
	while (i < len)
	{
		str2[i] = c;
		i++;
	}
	return (str);
}
