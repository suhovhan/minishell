/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:45 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/25 18:06:30 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*search_infile(t_filename *head, int pipe_index)
{
	while (head)
	{
		if (head->pipe_index == pipe_index)
			return (ft_strdup(head->filename));
		head = head->next;
	}
	return (NULL);
}

void	set_pipelist(t_addres *addres)
{
	t_token	*tmp;
	char	**cmd;
	char	*infile;
	int		outfile;
	int		i;

	i = -1;
	tmp = addres->token;
	while (++i <= addres->pipe_count)
	{
		infile = search_infile(addres->infile, i);
		outfile = addres->descriptor_output[i];
		cmd = cmd_line(tmp);
		while (tmp && tmp->type != _PIPE)
			tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
		append_pipeexec(&addres->pipe_list, cmd, infile, outfile);
	}
}

void	open_infile(t_pipe_exec **pipelist)
{
	t_pipe_exec *tmp;

	tmp = *pipelist;
	while (tmp)
	{
		tmp->fd_infile = -1;
		if (tmp->infile && *tmp->infile)
			tmp->fd_infile = open(tmp->infile, O_RDONLY);
		tmp = tmp->next;
	}
}

