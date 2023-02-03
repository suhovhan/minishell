/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:30:41 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 16:33:42 by suhovhan         ###   ########.fr       */
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

void	add_infile(t_addres *addres, char *filename, \
int pipe_index, int input_index)
{
	t_filename	*tmp;

	tmp = addres->infile;
	while (tmp)
	{
		if (tmp->pipe_index == pipe_index && tmp->input_index < input_index)
		{
			free(tmp->filename);
			tmp->filename = filename;
			tmp->input_index = input_index;
		}
		tmp = tmp->next;
	}
}

void	heredoc_external_helper(t_env *env, char **heredoc_tmp, int descriptor)
{
	char	*ptr;
	char	*expression;

	while (heredoc_tmp && *heredoc_tmp && **heredoc_tmp)
	{
		if (heredoc_tmp && *heredoc_tmp && **heredoc_tmp && \
		**heredoc_tmp == '$')
		{
			ptr = execute_expression(heredoc_tmp);
			if (ft_strlen(ptr) == 0)
				write(descriptor, "$", 1);
			expression = find_value_env(env, ptr);
			if (expression && *expression)
				write(descriptor, expression, ft_strlen(expression));
			free(expression);
			free(ptr);
			expression = NULL;
		}
		else
		{
			write(descriptor, &(**heredoc_tmp), 1);
			(*heredoc_tmp)++;
		}
	}
	write(descriptor, "\n", 1);
}

int	run_heredoc_external(t_env *env, char *token, int descriptor)
{
	char	*heredoc;
	char	*heredoc_tmp;

	while (1)
	{
		heredoc = readline("> ");
		if (!heredoc)
			break ;
		heredoc_tmp = heredoc;
		if (!ft_strcmp(heredoc_tmp, token))
		{
			free(heredoc);
			heredoc = NULL;
			return (0);
		}
		heredoc_external_helper(env, &heredoc_tmp, descriptor);
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
		if (!heredoc)
			break ;
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
