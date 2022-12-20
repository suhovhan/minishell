/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 02:51:14 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/20 02:18:24 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_heredoc_del(char **get_line)
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
	if (**get_line == _SINGLE_QUOTE)
		str = ft_cleanline(fill_word(get_line, _SINGLE_QUOTE, 1));
	else if (**get_line == _DUBLE_QUOTE)
		str = ft_cleanline(fill_word(get_line, _DUBLE_QUOTE, 1));
	else
		str = ft_cleanline(fill_word(get_line, ' ', 1));
	return (str);
}

int	run_heredoc_external(t_env *env, char *token, int descriptor)
{
	char	*heredoc;
	char	*heredoc_tmp;
	char	*expression;

	while (1)
	{
		heredoc = readline("> ");
		heredoc_tmp = heredoc;
		if (ft_strlen(heredoc) == ft_strlen(token) && \
		!ft_strncmp(heredoc, token, ft_strlen(token)))
		{
			free(heredoc);
			return (0);
		}
		while (heredoc && *heredoc)
		{
			if (heredoc && *heredoc && *heredoc == '$')
			{
				expression = execute_expression(&heredoc);
				if (ft_strlen(expression) == 0)
					write(descriptor, "$", 1);
				expression = find_value_env(env, expression);
				if (expression && *expression)
					write(descriptor, expression, ft_strlen(expression));
				free(expression);
			}
			else
			{
				write(descriptor, &(*heredoc), 1);
				heredoc++;
			}
		}
		write(descriptor, "\n", 1);
		free(heredoc_tmp);
	}
	return (0);
}

int	run_heredoc_expansion(char *token, int descriptor)
{
	char	*heredoc;

	while (1)
	{
		heredoc = readline("> ");
		if (ft_strlen(heredoc) == ft_strlen(token) && \
		!ft_strncmp(heredoc, token, ft_strlen(token)))
		{
			free(heredoc);
			return (0);
		}
		write(descriptor, heredoc, ft_strlen(heredoc));
		write(descriptor, "\n", 1);
		free(heredoc);
	}
	return (0);
}

void	run_heredoc(t_addres *addres, char *token, int type)
{
	t_env	*env;
	char	*del;
	int		descriptor;

	env = addres->env;
	del = ft_strjoin(".heredoc_\7", token);
	descriptor = open(del, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (type == _EXTERNAL)
		run_heredoc_external(env, token, descriptor);
	else
		run_heredoc_expansion(token, descriptor);
	addres->descriptor_input = descriptor;
	dup2(0, descriptor);
	close(descriptor);
	unlink(del);
}

int	heredoc(t_addres *addres)
{
	t_token	*ptr;
	t_token	*tmp;
	int		index;
	
	tmp = addres->token;
	ptr = addres->token;
	while (tmp && tmp->type != _PIPE)
	{
		if (tmp && tmp->type == _HEREDOC)
		{
			index = tmp->index;
			tmp = tmp->next;
			remove_node_from_token(&(addres->token), index);
			run_heredoc(addres, tmp->token, tmp->type);
			index = tmp->index;
			tmp = tmp->next;
			remove_node_from_token(&(addres->token), index);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}
