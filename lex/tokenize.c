/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:21 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/20 05:27:55 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fill_spaces(char **get_line, t_token **token)
{
	while (**get_line == ' ')
		(*get_line)++;
	(*get_line)--;
	append_token(token, _SPACE, ft_strdup(" "));
	return (0);
}

int	fill_redirections(char **get_line, t_token **token)
{
	if (**get_line == '<')
	{
		(*get_line)++;
		if (**get_line == '<')
			append_token(token, _HEREDOC, ft_strdup("<<"));
		else
		{
			(*get_line)--;
			append_token(token, _RED_IN, ft_strdup("<"));
		}
	}
	else if (**get_line == '>')
	{
		(*get_line)++;
		if (**get_line == '>')
			append_token(token, _APPEND, ft_strdup(">>"));
		else
		{
			(*get_line)--;
			append_token(token, _RED_OUT, ft_strdup(">"));
		}
	}
	return (0);
}

int	fill_quotes_external(char **get_line, t_token **token, int quote)
{
	int	i;

	if (quote == 39)
	{
		**get_line = _SINGLE_QUOTE;
		i = _EXPANSION_SINGLE;
	}
	else
	{
		**get_line = _DUBLE_QUOTE;
		i = _EXPANSION_DUBLE;
	}
	if (**get_line != '\0' && **get_line != quote)
			append_token(token, i, fill_word(get_line, quote, 0));
	if (**get_line == quote)
	{
		if (quote == 39)
			**get_line = _SINGLE_QUOTE;
		else
			**get_line = _DUBLE_QUOTE;
	}
	return (0);
}

void	fill_external(char **get_line, t_token **token)
{
	char	*res;
	char	*line;
	int		i;

	i = -1;
	res = malloc(sizeof(char) * ft_strlen(*get_line));
	while (**get_line == ' ')
		res[++i] = ' ';
		while (**get_line != '\0' && (**get_line != ' ' && **get_line != '<' \
			&& **get_line != '>' && **get_line != '|' && **get_line != '$' \
			&& **get_line != '"' && **get_line != 39) && res)
		{
			res[++i] = **get_line;
			(*get_line)++;
		}
	res[++i] = '\0';
	line = (char*)malloc(sizeof(char) * ft_strlen(res));
	i = -1;
	while (res[++i])
		line[i] = res[i];
	free(res);
	(*get_line)--;
	append_token(token, _EXTERNAL, line);
}

void	fill_expression(char **get_line, t_token **token)
{
	char	*res;
	char	*line;
	int		i;

	i = -1;
	res = (char*)malloc(sizeof(char) * ft_strlen(*get_line));
	res[++i] = **get_line;
	(*get_line)++;
		while (**get_line != '\0' && (**get_line != ' ' && **get_line != '<' \
			&& **get_line != '>' && **get_line != '|' && **get_line != '$' \
			&& **get_line != 39 && **get_line != '"') && res)
		{
			res[++i] = **get_line;
			(*get_line)++;
		}
	res[++i] = '\0';
	line = (char*)malloc(sizeof(char) * ft_strlen(res));
	i = -1;
	while (res[++i])
		line[i] = res[i];
	line[i] = '\0';
	(*get_line)--;
	free(res);
	append_token(token, _EXPRESSION, ft_strdup(line));
	free(line);
}

void	set_token(char **get_line, t_token **token)
{
	while (**get_line)
	{
		if (**get_line == ' ')
			fill_spaces(get_line, token);
		else if (**get_line == '|')
			append_token(token, _PIPE, ft_strdup("|"));
		else if (**get_line == '$')
			fill_expression(get_line, token);
		else if (**get_line == 39)
			fill_quotes_external(get_line, token, 39);
		else if (**get_line == '"')
			fill_quotes_external(get_line, token, '"');
		else if (**get_line == '<' || **get_line == '>')
			fill_redirections(get_line, token);
		else
			fill_external(get_line, token);
		(*get_line)++;
	}
	clean_space_from_token(token);
}
