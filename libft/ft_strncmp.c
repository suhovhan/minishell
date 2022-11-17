/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 21:34:38 by suhovhan          #+#    #+#             */
/*   Updated: 2022/05/10 02:32:04 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned const char	*c1;
	unsigned const char	*c2;
	size_t				i;

	c1 = (unsigned const char *)s1;
	c2 = (unsigned const char *)s2;
	i = 0;
	while (i < n)
	{
		if ((c1[i] != c2[i] || s1[i] == 0) || s2[i] == 0)
			return (c1[i] - c2[i]);
		i++;
	}
	return (0);
}
