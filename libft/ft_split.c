/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 12:42:23 by suhovhan          #+#    #+#             */
/*   Updated: 2022/11/23 20:05:18 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordlen(const char *s, char c)
{
	size_t	index;

	index = 0;
	while (*s)
	{
		index++;
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			index--;
		while (*s && *s != c)
			s++;
	}
	return (index);
}

static char	**fill_string(char **store, const char *s, char c)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c)
			{
				len++;
				s++;
			}
			store[i++] = ft_substr(s - len, 0, len);
		}
		else
			s++;
	}
	store[i] = 0;
	return (store);
}

char	**ft_split(const char *s, char c)
{
	char	**split_string;
	size_t	len_words;

	if (!s)
		return (NULL);
	len_words = wordlen(s, c);
	split_string = malloc(sizeof(char *) * (len_words + 1));
	if (!split_string)
		return (NULL);
	split_string = fill_string(split_string, s, c);
	return (split_string);
}
