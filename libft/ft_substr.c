/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:35:02 by suhovhan          #+#    #+#             */
/*   Updated: 2022/05/10 02:00:05 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	l;
	size_t	j;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (start > l || len == 0)
		j = 0;
	else if (l - start + 1 > len)
		j = len;
	else
		j = l - start;
	str = (char *)malloc(sizeof(char) * (j + 1));
	if (!str)
		return (0);
	l = 0;
	while (s[start] && l < j)
		str[l++] = s[start++];
	str[l] = '\0';
	return (str);
}
