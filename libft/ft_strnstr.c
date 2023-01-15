/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 23:27:04 by suhovhan          #+#    #+#             */
/*   Updated: 2022/04/26 14:47:43 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		lenght;
	char	*large;
	char	*small;

	if (*needle == '\0')
		return ((char *)haystack);
	large = (char *)haystack;
	small = (char *)needle;
	i = 0;
	lenght = ft_strlen(small);
	while (large[i] != '\0' && (i + lenght) <= len)
	{
		if (ft_strncmp((large + i), small, lenght) == 0)
			return (large + i);
		i++;
	}
	return (0);
}
