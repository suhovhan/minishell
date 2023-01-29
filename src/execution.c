/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:04:41 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/29 13:27:53 by suhovhan         ###   ########.fr       */
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
		{
			waitpid(pid, &addres->exit_status, 0);
			if (WIFEXITED(addres->exit_status))
				addres->exit_status = WEXITSTATUS(addres->exit_status);
			else if (WIFSIGNALED(addres->exit_status))
			{
				if (addres->exit_status == SIGQUIT)
					write(1, "Quit: 3\n", 8);
				else if (addres->exit_status == SIGINT)
					write(1, "\n", 1);
				addres->exit_status += 128;
			}
		}
		else
		{
			path = env_path(addres->env);
			addres->cmd_line[0] = check_path(addres->cmd_line[0], path);
			// execve(addres->cmd_line[0], addres->cmd_line, env);
			if (execve(addres->cmd_line[0], addres->cmd_line, env) == -1)
			{
				fprintf(stderr, "minishell-$: %s : No such file or directory\n", addres->cmd_line[0]);
			}
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

void	child_proc(t_addres *addres, t_pipe_exec *tmp, char **env, int (*fds)[2], int i)
{
	char	**path;

	if(i == 0)
	{
		if (tmp->fd_infile != -1)
		{
			dup2(tmp->fd_infile, 0);
			close(tmp->fd_infile);
		}
		if (tmp->output != -1)
		{
			dup2(tmp->output, 1);
			close(tmp->output);
		}
		else
			dup2(fds[i][1], 1);
		close(fds[i][0]);
		close(fds[i][1]);
		if (isbuiltin(tmp->cmd_line, addres) == -1)
		{
			path = env_path(addres->env);
			tmp->cmd_line[0] = check_path(tmp->cmd_line[0], path);
			execve(tmp->cmd_line[0], tmp->cmd_line, env);
		}
		exit(0);
	}
	else if (i < addres->pipe_count)
	{
		if (tmp->fd_infile != -1)
		{
			dup2(tmp->fd_infile, 0);
			close(tmp->fd_infile);
		}
		else
			dup2(fds[i - 1][0], 0);
		if (tmp->output != -1)
		{
			dup2(tmp->output, 1);
			close(tmp->output);
		}
		else
			dup2(fds[i][1], 1);
		close(fds[i - 1][0]);
		close(fds[i - 1][1]);
		close(fds[i][0]);
		close(fds[i][1]);
		if (isbuiltin(tmp->cmd_line, addres) == -1)
		{
			path = env_path(addres->env);
			tmp->cmd_line[0] = check_path(tmp->cmd_line[0], path);
			execve(tmp->cmd_line[0], tmp->cmd_line, env);
		}
		exit(0);
	}
	else 
	{
		if (tmp->fd_infile != -1)
		{
			dup2(tmp->fd_infile, 0);
			close(tmp->fd_infile);
		}
		else
			dup2(fds[i - 1][0], 0);
		if (tmp->output != -1)
		{
			dup2(tmp->output, 1);
			close(tmp->output);
		}
		close(fds[i - 1][0]);
		close(fds[i - 1][1]);
		if (isbuiltin(tmp->cmd_line, addres) == -1)
		{
			path = env_path(addres->env);
			tmp->cmd_line[0] = check_path(tmp->cmd_line[0], path);
			execve(tmp->cmd_line[0], tmp->cmd_line, env);
		}
		exit(0);
	}
}

void	pipe_execution(t_addres *addres, char **env)
{
	t_pipe_exec	*tmp;
	int		*pid;
	int 	(*fds)[2];
	int i = -1;

	fds = malloc(sizeof(int *) * addres->pipe_count);
	if(!fds)
		return ;
	pid = (int *)malloc(sizeof(int) * (addres->pipe_count + 1));
	if(!pid)
		return ;
	set_pipelist(addres);
	open_infile(&addres->pipe_list);
	tmp = addres->pipe_list;
	while(++i < addres->pipe_count)
		pipe(fds[i]);
	i = -1;
	while(++i <= addres->pipe_count)
	{
		pid[i] = fork();
		if (pid[i] == -1) // kill all processes
			exit (1);
		if (pid[i] == 0)
			child_proc(addres, tmp, env, fds, i);
		if (i < addres->pipe_count)
			close(fds[i][1]);
		if (i > 0)
			close(fds[i - 1][0]);
		tmp = tmp->next;
	}
	i = -1;
	while(++i <= addres->pipe_count)
	{
		waitpid(pid[i], &addres->exit_status, 0);
		if (WIFEXITED(addres->exit_status))
			;
		else if (WIFSIGNALED(addres->exit_status))
		{
			if (addres->exit_status == SIGQUIT && i == addres->pipe_count + 1)
				write(1, ":Quit 3\n", 8);
			else if (addres->exit_status == SIGINT && i == addres->pipe_count + 1)
				write(1, "\n", 1);
			addres->exit_status += 128;
		}
	}
	free(fds);
	free(pid);
}
