/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smart_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:04:32 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/10 19:28:06 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_wordcount_smartsplit(char *str)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			while (str[++i] != '"')
				;
		if (str[i] == 39)
			while (str[++i] != 39)
				;
		if (str[i] == '|')
			count++;
	}
	return (count);
}

char *fill_word_smartsplit(char *str, int start, int end)
{
	int		len;
	char	*res;

	len = end - start;
	if (len < 0)
		return (NULL);
	res = (char*)malloc(sizeof(char) * (len + 1));
	res[len] = '\0';
	while (start < end)
		res[--len] = str[--end];	
	return (res);
}

char	**ft_smart_split(char *str, int i, int j)
{
	//i = -1;
	//j = -1;
	char	**res;
	int		start;

	res = (char**)malloc(sizeof(char*) * (get_wordcount_smartsplit(str) + 2));
	start = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			while (str[++i] != '"')
				;
		if (str[i] == 39)
			while (str[++i] != 39)
				;
		if (str[i] == '|')
		{
			res [++j] = fill_word_smartsplit(str, start, i);
			start = i + 1;
		}
	}
	res [++j] = fill_word_smartsplit(str, start, i);
	res[++j] = 0;
	return (res);
}