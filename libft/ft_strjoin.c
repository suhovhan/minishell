/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:39:26 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/26 17:02:15 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
			i++;
	if (s2)
		while (s2[j])
			j++;
	new = (char *)malloc(i + j + 1);
	if (!new)
		return (NULL);
	ft_memmove(new, s1, i + 1);
	ft_strlcat(new, s2, i + j + 1);
	return (new);
}
