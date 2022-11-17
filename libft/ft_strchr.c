/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 20:24:16 by suhovhan          #+#    #+#             */
/*   Updated: 2022/05/10 01:54:31 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	if (ch == 0)
		return ((char *)str + ft_strlen(str));
	while (*str != '\0')
	{
		if (*str == (char)ch)
			return ((char *)str);
		str++;
	}
	return (0);
}
