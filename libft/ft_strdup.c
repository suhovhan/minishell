/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:02:52 by suhovhan          #+#    #+#             */
/*   Updated: 2022/04/26 12:31:38 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new;
	int		len;

	if (!s1)
		return (NULL);
	len = ft_strlen((char *)s1);
	new = (char *)malloc(len + 1);
	ft_strlcpy(new, s1, len + 1);
	return (new);
}
