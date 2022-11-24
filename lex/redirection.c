/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 04:55:47 by suhovhan          #+#    #+#             */
/*   Updated: 2022/11/24 13:47:21 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_redir_in(char **get_line, t_redirection **redir)
{
	char *str;
	while (**get_line != '<')
		(*get_line)++;
	**get_line = _RED_IN;
	(*get_line)++;
	while (**get_line == ' ')
		(*get_line)++;
	str = fill_word(get_line, ' ', 1);
	append_redir(redir, str, _RED_IN);
	return (0);
}

int	set_redir_out(char **get_line, t_redirection **redir)
{
	char	*str;
	while (**get_line != '>')
		(*get_line)++;
	**get_line = _RED_IN;
	(*get_line)++;
	while (**get_line == ' ')
		(*get_line)++;
	str = fill_word(get_line, ' ', 1);
	append_redir(redir, str, _RED_OUT);
	return (0);
}

int	set_redir_append(char **get_line, t_redirection **redir)
{
	char	*str;
	while (**get_line != '>')
		(*get_line)++;
	**get_line = _RED_IN;
	(*get_line)++;
	**get_line = _RED_IN;
	(*get_line)++;
	while (**get_line == ' ')
		(*get_line)++;
	str = fill_word(get_line, ' ', 1);
	append_redir(redir, str, _APPEND);
	return (0);
}

int	set_redir_heredoc(char **get_line, t_redirection **redir)
{
	char *str;
	while (**get_line != '<')
		(*get_line)++;
	**get_line = _RED_IN;
	(*get_line)++;
	**get_line = _RED_IN;
	(*get_line)++;
	while (**get_line == ' ')
		(*get_line)++;
	str = fill_word(get_line, ' ', 1);
	append_redir(redir, str, _HEREDOC);
	return (0);
}

int	set_redirection(t_separators *sep, t_redirection **redir, char **get_line)
{
	while (sep && sep->sep != _PIPE)
	{
		if (sep->sep == _RED_IN)
			set_redir_in(get_line, redir);
		if (sep->sep == _RED_OUT)
			set_redir_out(get_line, redir);
		if (sep->sep == _HEREDOC)
			set_redir_heredoc(get_line, redir);
		if (sep->sep == _APPEND)
			set_redir_append(get_line, redir);
		sep = sep->next;
	}
	return (0);
}
