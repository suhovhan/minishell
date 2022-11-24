/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:21 by suhovhan          #+#    #+#             */
/*   Updated: 2022/11/22 16:27:47 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fill_spaces(char **get_line, t_separators **separators)
{
	while (**get_line == ' ')
		(*get_line)++;
	(*get_line)--;
	append_sep(separators, _SPACE);
	return (0);
}

int	fill_redirections(char **get_line, t_separators **separators)
{
	if (**get_line == '<')
	{
		(*get_line)++;
		if (**get_line == '<')
			append_sep(separators, _HEREDOC);
		else
		{
			(*get_line)--;
			append_sep(separators, _RED_IN);
		}
	}
	else if (**get_line == '>')
	{
		(*get_line)++;
		if (**get_line == '>')
			append_sep(separators, _APPEND);
		else
		{
			(*get_line)--;
			append_sep(separators, _RED_OUT);
		}
	}
	return (0);
}

int	fill_quotes_external(char **get_line, t_separators **separators, int quote)
{
	if (quote == 39)
		**get_line = _SINGLE_QUOTE;
	else
		**get_line = _DUBLE_QUOTE;
	(*get_line)++;
	if (**get_line != '\0' && **get_line != quote)
		append_sep(separators, _EXTERNAL);
		while (**get_line != '\0' && **get_line != quote)
			(*get_line)++;
	if (**get_line == quote)
	{
		if (quote == 39)
		{
			**get_line = _SINGLE_QUOTE;
			append_sep(separators, _SINGLE_QUOTE);
		}
		else
		{
			**get_line = _DUBLE_QUOTE;
			append_sep(separators, _DUBLE_QUOTE);
		}
	}
	return (0);
}

int	fill_external(char **get_line, t_separators **separators)
{
	(*get_line)++;
	append_sep(separators, _EXTERNAL);
		while (**get_line != '\0' && \
			(**get_line != ' ' && \
			**get_line != '<' && \
			**get_line != '>' && \
			**get_line != '|' && \
			**get_line != '$' && \
			**get_line != 39 && \
			**get_line != '"'))
			(*get_line)++;
	(*get_line)--;
	return (0);
}

void	set_sep(char **get_line, t_separators **separators)
{
	while (**get_line)
	{
		if (**get_line == ' ')
			fill_spaces(get_line, separators);
		else if (**get_line == '|')
			append_sep(separators, _PIPE);
		else if (**get_line == '$')
			append_sep(separators, _EXPRESSION);
		else if (**get_line == 39)
		{
			append_sep(separators, _SINGLE_QUOTE);
			fill_quotes_external(get_line, separators, 39);
		}
		else if (**get_line == '"')
		{
			append_sep(separators, _DUBLE_QUOTE);
			fill_quotes_external(get_line, separators, '"');
		}
		else if (**get_line == '<' || **get_line == '>')
			fill_redirections(get_line, separators);
		else
			fill_external(get_line, separators);
		(*get_line)++;
	}
}
