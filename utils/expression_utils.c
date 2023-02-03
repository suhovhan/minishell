/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:30:51 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 13:33:48 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_key_expression(char c)
{
	if (c && ((c >= 'a' && c <= 'z') || \
	(c >= 'A' && c <= 'Z') || \
	(c >= '0' && c <= '9') || \
	c == '-' || c == '_'))
		return (0);
	return (-1);
}

int	get_wordlen_expression(char **heredoc)
{
	char	*heredoc_line;
	int		i;

	i = 0;
	heredoc_line = *heredoc;
	if (heredoc_line && *heredoc_line && *heredoc_line >= '0' && \
	*heredoc_line <= '9')
		return (-1);
	while (heredoc_line && *heredoc_line && \
	((*heredoc_line >= 'a' && *heredoc_line <= 'z') || \
	(*heredoc_line >= 'A' && *heredoc_line <= 'Z') || \
	(*heredoc_line >= '0' && *heredoc_line <= '9') || \
	*heredoc_line == '-' || *heredoc_line == '_'))
	{
		heredoc_line++;
		i++;
	}
	return (i);
}

char	*execute_expression(char **heredoc)
{
	char	*res;
	int		i;

	i = -1;
	if (heredoc && *heredoc && **heredoc && **heredoc == '$')
	{
		(*heredoc)++;
		if (**heredoc == '?')
		{
			(*heredoc)++;
			return (ft_strdup("?"));
		}
		if (get_wordlen_expression(heredoc) == -1)
			return ("(null)");
		res = malloc(sizeof(char) * (get_wordlen_expression(heredoc) + 1));
	}
	while (heredoc && *heredoc && **heredoc && \
	(check_key_expression(**heredoc) == 0))
	{
		res[++i] = **heredoc;
		(*heredoc)++;
	}
	res[++i] = '\0';
	return (res);
}
