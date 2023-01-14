/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:41:59 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/18 00:56:00 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_single_quotes(char **get_line)
{
	int	single = 0;

	single++;
	(*get_line)++;
	while (get_line && *get_line && **get_line)
	{
		if (get_line && *get_line && **get_line == 39)
		{
			single++;
			break;
		}
		else
			(*get_line)++;
	}
	return (single);
}

int	check_duble_quotes(char **get_line)
{
	int	duble = 0;

	duble++;
	(*get_line)++;
	while (get_line && *get_line && **get_line)
	{
		if (get_line && *get_line && **get_line == '"')
		{
			duble++;
			break;
		}
		else
			(*get_line)++;
	}
	return (duble);
}

int	check_quotes(char *get_line)
{
	int	single;
	int	duble;

	single = 0;
	duble = 0;
	while (get_line && *get_line)
	{
		if (get_line && *get_line && *get_line == 39)
			single += check_single_quotes(&get_line);
		if (get_line && *get_line && *get_line == '"')
			duble += check_duble_quotes(&get_line);
		get_line++;
	}
	if (duble % 2 || single % 2)
	{
		print_syntax_error(1);
		return (1);
	}
	return (0);
}

int	check_redirections(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == _RED_IN || token->type == _RED_OUT || \
			token->type == _APPEND)
		{
			token = token->next;
			// while (token && token->type == _SPACE)
			// 	token = token->next;
			if (token == NULL || (token->type != _EXTERNAL && token->type != _EXPRESSION && \
			token->type != _EXPANSION_DUBLE && token->type != _EXPANSION_SINGLE))
			{
				print_syntax_error(1);
				return (-1);
			}
		}
		token = token->next;
	}
	return (0);
}

int	check_heredoc(t_addres *addres)
{
	int	i;
	t_token	*tmp;

	i = 0;
	tmp = addres->token;
	while (tmp != NULL)
	{
		if (tmp->type == _HEREDOC)
		{
			if (++i > 16)
				exit_shell(addres, _HEREDOC);
			tmp = tmp->next;
			while (tmp != NULL && tmp->type == _SPACE)
				tmp = tmp->next;
			if (tmp == NULL || (tmp->type != _EXTERNAL && \
			tmp->type != _EXPANSION_DUBLE && tmp->type != _EXPANSION_SINGLE && \
			tmp->type != _EXPRESSION))
			{
				print_syntax_error(1);
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_pipe(t_token *token)
{
	if (token != NULL && token->type == _SPACE)
		token = token->next;
	if (token != NULL && token->type == _PIPE)
		return (-1);
	while (token != NULL)
	{
		if (token != NULL && token->type == _PIPE)
		{
			token = token->next;
			if (token != NULL && token->type == _SPACE)
				token = token->next;
			if (token == NULL || token->type == _PIPE)
				return (-1);
		}
		if (token != NULL)
			token = token->next;
	}
	return (0);
}

int	check_syntax(t_token *token)
{
	if (token == NULL)
		return (0);
	if (check_pipe(token) == -1)
	{
		print_syntax_error(124);
		return (-1);
	}
	if (check_redirections(token) == -1)
		return (-1);
	return (0);
}
