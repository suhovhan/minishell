/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:21 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/21 20:14:53 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fill_spaces(char **get_line, t_token **token)
{
	while (**get_line == ' ')
		(*get_line)++;
	(*get_line)--;
	append_token(token, _SPACE, ft_strdup(" \0"));
	return (0);
}

int	fill_redirections(char **get_line, t_token **token)
{
	if (**get_line == '<')
	{
		(*get_line)++;
		if (**get_line == '<')
			append_token(token, _HEREDOC, ft_strdup("<<\0"));
		else
		{
			(*get_line)--;
			append_token(token, _RED_IN, ft_strdup("<\0"));
		}
	}
	else if (**get_line == '>')
	{
		(*get_line)++;
		if (**get_line == '>')
			append_token(token, _APPEND, ft_strdup(">>\0"));
		else
		{
			(*get_line)--;
			append_token(token, _RED_OUT, ft_strdup(">\0"));
		}
	}
	return (0);
}

int	fill_quotes_external(char **get_line, t_token **token, int quote)
{
	int	type;

	if (quote == 39)
		type = _EXPANSION_SINGLE;
	else
		type = _EXPANSION_DUBLE;
	(*get_line)++;
	if (**get_line != '\0' && **get_line != quote)
			append_token(token, type, fill_word(get_line, quote, 0));
	return (0);
}

void	fill_external(char **get_line, t_token **token)
{
	char	*res;
	char	*line;
	int		i;

	i = -1;
	res = malloc(sizeof(char) * (ft_strlen(*get_line) + 1));
	while (**get_line == ' ')
		res[++i] = ' ';
		while (**get_line != '\0' && (**get_line != ' ' && **get_line != '<' \
			&& **get_line != '>' && **get_line != '|' \
			&& **get_line != '"' && **get_line != 39) && res)
		{
			res[++i] = **get_line;
			(*get_line)++;
		}
	res[++i] = '\0';
	line = (char*)malloc(sizeof(char) * (ft_strlen(res) + 1));
	i = -1;
	while (res[++i])
		line[i] = res[i];
	line[i] = '\0';
	free(res);
	res = NULL;
	(*get_line)--;
	append_token(token, _EXTERNAL, line);
}

void	set_token(t_token **token, char **get_line)
{
	while (**get_line)
	{
		if (**get_line == ' ')
			fill_spaces(get_line, token);
		else if (**get_line == '|')
			append_token(token, _PIPE, ft_strdup("|"));
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
}
