/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:41:59 by suhovhan          #+#    #+#             */
/*   Updated: 2022/11/22 17:19:03 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(t_separators *separators)
{
	while (separators != NULL)
	{
		if (separators != NULL && separators->sep == _SINGLE_QUOTE)
		{
			separators = separators->next;
			while (separators != NULL && separators->sep != _SINGLE_QUOTE)
				separators = separators->next;
			if (separators == NULL || separators->sep != _SINGLE_QUOTE)
			{
				print_syntax_error(39);
				return (-1);
			}
		}
		if (separators != NULL && separators->sep == _DUBLE_QUOTE)
		{
			separators = separators->next;
			while (separators != NULL && separators->sep != _DUBLE_QUOTE)
				separators = separators->next;
			if (separators == NULL || separators->sep != _DUBLE_QUOTE)
			{
				print_syntax_error(34);
				return (-1);
			}
		}
		separators = separators->next;
	}
	return (0);
}

int	check_redirections(t_separators *separators)
{
	while (separators != NULL)
	{
		if (separators->sep == _RED_IN || separators->sep == _RED_OUT || \
			separators->sep == _HEREDOC || separators->sep == _APPEND)
		{
			separators = separators->next;
			while (separators != NULL && (separators->sep == _SPACE || \
			separators->sep == _SINGLE_QUOTE || separators->sep == _DUBLE_QUOTE ||\
			separators->sep == _EXPANSION))
				separators = separators->next;
			if (separators == NULL || (separators->sep != _EXTERNAL && separators->sep != _EXPRESSION))
			{
				print_syntax_error(1);
				return (-1);
			}
		}
		separators = separators->next;
	}
	return (0);
}

int	check_pipe(t_separators *separators)
{
	if (separators != NULL && separators->sep == _SPACE)
		separators = separators->next;
	if (separators != NULL && separators->sep == _PIPE)
		return (-1);
	while (separators != NULL)
	{
		if (separators != NULL && separators->sep == _PIPE)
		{
			separators = separators->next;
			if (separators != NULL && separators->sep == _SPACE)
				separators = separators->next;
			if (separators == NULL || separators->sep == _PIPE)
				return (-1);
		}
		if (separators != NULL)
			separators = separators->next;
	}
	return (0);
}

int	check_separators(t_separators *separators)
{
	if (check_quotes(separators) == -1)
		return (-1);
	if (check_pipe(separators) == -1)
	{
		print_syntax_error(124);
		return (-1);
	}
	if (check_redirections(separators) == -1)
		return (-1);
	return (0);
}
