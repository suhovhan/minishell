/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 02:51:14 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/21 19:54:23 by suhovhan         ###   ########.fr       */
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
	str = NULL;
	str = ft_strjoin(del, name);
	free(del);
	del = NULL;
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
			heredoc = NULL;
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
				expression = NULL;
			}
			else
			{
				write(descriptor, &(*heredoc_tmp), 1);
				heredoc_tmp++;
			}
		}
		write(descriptor, "\n", 1);
		free(heredoc);
		heredoc = NULL;
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
			heredoc = NULL;
			return (0);
		}
		write(descriptor, heredoc, ft_strlen(heredoc));
		write(descriptor, "\n", 1);
		free(heredoc);
		heredoc = NULL;
	}
	return (0);
}

char	*run_heredoc(t_addres *addres, char *token, int type, int index)
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
	close(addres->descriptor_input);
	return (del);
}

void	add_infile(t_addres *addres, char *filename, int pipe_index, int input_index)
{
	t_filename	*tmp;

	tmp = addres->infile;
	while (tmp)
	{
		if (tmp->pipe_index == pipe_index && tmp->input_index < input_index)
		{
			tmp->filename = filename;
			tmp->input_index = input_index;
		}
		tmp = tmp->next;
	}
}

int	heredoc(t_addres *addres)
{
	t_token	*ptr;
	t_token	*tmp;
	int		index;
	char	*del;
	int		pipe_index;

	pipe_index = 0;
	tmp = addres->token;
	ptr = addres->token;
	while (tmp)
	{
		if (tmp->type == _PIPE)
			pipe_index++;
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
			if (!tmp || (tmp->type != _EXTERNAL && tmp->type != _EXPANSION_SINGLE \
			&& tmp->type != _EXPANSION_DUBLE))
			{
				print_syntax_error(1);
				return (-1);
			}
			del = run_heredoc(addres, tmp->token, tmp->type, tmp->index);
			add_infile(addres, del, pipe_index, tmp->index);
			index = tmp->index;
			tmp = tmp->next;
			remove_node_from_token(&(addres->token), index);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}
