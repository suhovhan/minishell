/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:04:41 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/21 16:32:25 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_zeropipe(t_addres *addres, char **env)
{
	int		pid;
	char	**path;

	path = NULL;
	addres->cmd_line = cmd_line(addres->token);
	if (addres->infile)
		addres->descriptor_input = open(addres->infile->filename, O_RDONLY);
	dup2(addres->descriptor_input, 0);
	if (addres->descriptor_output[0])
		dup2(addres->descriptor_output[0], 1);
	close(addres->descriptor_input);
	close(addres->descriptor_output[0]);
	if (isbuiltin(addres->cmd_line, addres) == -1)
	{
		pid = fork();
		if (pid)
			wait(&pid);
		else
		{
			path = env_path(addres->env);
			addres->cmd_line[0] = check_path(addres->cmd_line[0], path);
			execve(addres->cmd_line[0], addres->cmd_line, env);
			exit(127);
		}
	}
	dup2(addres->std_out_copy, 1);
	dup2(addres->std_input_copy, 0);
	free_mtx(addres->cmd_line);
	free_mtx(path);
}

void	execution(t_addres *addres, char **env)
{
	if (addres->pipe_count == 0)
		exec_zeropipe(addres, env);
	else if (addres->pipe_count > 0)
		pipe_execution(addres, env);
}

void	pipe_execution(t_addres *addres, char **env)
{
	t_pipe_exec	*tmp;
	int (*fds)[2];
	int	pid;
	char	**path;

	fds = malloc(sizeof(int *) * addres->pipe_count);
	if(!fds)
		return ;
	int i = -1;
	while(++i < addres->pipe_count)
		pipe(fds[i]);
	i = -1;
	set_pipelist(addres);
	open_infile(&addres->pipe_list);
	tmp = addres->pipe_list;
	while(tmp)
	{
		if(++i == 0)
		{
			pid = fork();
			if (pid)
				wait(&pid);
			else
			{
				if (tmp->fd_infile != -1)
					dup2(tmp->fd_infile, 0);
				if (tmp->output != -1)
					dup2(tmp->output, 1);
				else
					dup2(fds[i][1], 1);
				if (isbuiltin(tmp->cmd_line, addres) == -1)
				{
					path = env_path(addres->env);
					tmp->cmd_line[0] = check_path(tmp->cmd_line[0], path);
					execve(tmp->cmd_line[0], tmp->cmd_line, env);
					exit(127);
				}
				exit(0);
			}
			close(fds[i][1]);
		}
		else 
		{
			pid = fork();
			if (pid)
				wait(&pid);
			else
			{
				if (tmp->fd_infile != -1)
					dup2(tmp->fd_infile, 0);
				else
					dup2(fds[i - 1][0], 0);
				if (tmp->output != -1)
					dup2(tmp->output, 1);
				if (isbuiltin(tmp->cmd_line, addres) == -1)
				{
					path = env_path(addres->env);
					tmp->cmd_line[0] = check_path(tmp->cmd_line[0], path);
					execve(tmp->cmd_line[0], tmp->cmd_line, env);
					exit(127);
				}
				exit(0);
			}
		}
		tmp = tmp->next;
	}
	free(fds);
}

