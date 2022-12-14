/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 02:51:14 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/28 06:11:34 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_heredoc_del(char *name, int index)
{
	char	*del;
	char	*str;
	

	str = ft_itoa(index);
	del = ft_strjoin("/var/tmp/hd_files/.heredoc_", str);
	free(str);
	str = ft_strjoin(del, name);
	free(del);
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
		if (ft_strlen(heredoc_tmp) == ft_strlen(token) && \
		!ft_strncmp(heredoc_tmp, token, ft_strlen(token)))
		{
			free(heredoc);
			return (0);
		}
		while (heredoc_tmp && *heredoc_tmp)
		{
			if (heredoc_tmp && *heredoc_tmp && *heredoc_tmp == '$')
			{
				expression = execute_expression(&heredoc_tmp);
				if (ft_strlen(expression) == 0)
					write(descriptor, "$", 1);
				expression = find_value_env(env, expression);
				if (expression && *expression)
					write(descriptor, expression, ft_strlen(expression));
				free(expression);
			}
			else
			{
				write(descriptor, &(*heredoc_tmp), 1);
				heredoc_tmp++;
			}
		}
		write(descriptor, "\n", 1);
		free(heredoc);
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

void	run_heredoc(t_addres *addres, char *token, int type, int index)
{
	t_env	*env;
	char	*del;
	int		descriptor;

	env = addres->env;
	del = get_heredoc_del(token, index);
	descriptor = open(del, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (type == _EXTERNAL)
		run_heredoc_external(env, token, descriptor);
	else
		run_heredoc_expansion(token, descriptor);
	if (index > addres->input_index)
	{
		addres->input_index = index;
		addres->input_filename = ft_strdup(del);
	}
	close(addres->descriptor_input);
	// close(descriptor);
	// descriptor = open(del, O_RDONLY, 0644);
	// addres->descriptor_input = descriptor;
	// dup2(descriptor, 0);
	// close(descriptor);
	// unlink(del);
	free(del);
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
			if (tmp && tmp->type == _SPACE)
			{
				index = tmp->index;
				tmp = tmp->next;
				remove_node_from_token(&(addres->token), index);
			}
			run_heredoc(addres, tmp->token, tmp->type, tmp->index);
			index = tmp->index;
			tmp = tmp->next;
			remove_node_from_token(&(addres->token), index);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}
