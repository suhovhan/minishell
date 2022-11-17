/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 20:31:21 by suhovhan          #+#    #+#             */
/*   Updated: 2022/04/26 13:57:42 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int		i;

	if (ch == 0)
		return ((char *)str + ft_strlen(str));
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char)ch)
			return ((char *)str + i);
		i--;
	}
	return (0);
}
