/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 02:51:14 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 16:32:56 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	heredoc_norm1(t_addres *addres, t_token **tmp)
{
	int		index;

	index = (*tmp)->index;
	(*tmp) = (*tmp)->next;
	remove_node_from_token(&(addres->token), index);
	if ((*tmp) && (*tmp)->type == _SPACE)
	{
		index = (*tmp)->index;
		(*tmp) = (*tmp)->next;
		remove_node_from_token(&(addres->token), index);
	}
}

int	heredoc_norm(t_addres *addres, t_token **tmp, int pipe_index)
{
	int		pid;
	int		index;

	heredoc_norm1(addres, tmp);
	if (!(*tmp) || ((*tmp)->type != _EXTERNAL && \
	(*tmp)->type != _EXPANSION_SINGLE \
	&& (*tmp)->type != _EXPANSION_DUBLE))
		return (-1);
	pid = fork();
	if (pid)
		wait(NULL);
	else
	{
		sig_main(3);
		run_heredoc(addres, (*tmp)->token, (*tmp)->type, (*tmp)->index);
		exit(0);
	}
	add_infile(addres, get_heredoc_del((*tmp)->token, \
	(*tmp)->index), pipe_index, (*tmp)->index);
	index = (*tmp)->index;
	(*tmp) = (*tmp)->next;
	remove_node_from_token(&(addres->token), index);
	return (0);
}

int	heredoc(t_addres *addres)
{
	t_token	*tmp;
	int		pipe_index;

	pipe_index = 0;
	tmp = addres->token;
	while (tmp)
	{
		if (tmp->type == _PIPE)
			pipe_index++;
		if (tmp && tmp->type == _HEREDOC)
		{
			if (heredoc_norm(addres, &tmp, pipe_index) == -1)
				return (-1);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}
