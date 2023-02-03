/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:04:41 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 17:19:51 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_cmd(t_addres *addres, t_pipe_exec *tmp, char **env)
{
	char	**path;
	char	*cmd;

	cmd = 0;
	if (isbuiltin(tmp->cmd_line, addres) == -1)
	{
		path = env_path(addres->env);
		cmd = ft_strdup(tmp->cmd_line[0]);
		tmp->cmd_line[0] = check_path(tmp->cmd_line[0], path, 0);
		execve(tmp->cmd_line[0], tmp->cmd_line, env);
		check_path(cmd, path, 1);
	}
}

void	first_cmd(t_addres *addres, t_pipe_exec *tmp, \
char **env, int (*fds)[2], int i)
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
	run_cmd(addres, tmp, env);
	exit(0);	
}

void	needle_cmd(t_addres *addres, t_pipe_exec *tmp, \
char **env, int (*fds)[2], int i)
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
	run_cmd(addres, tmp, env);
	exit(0);
}

void	last_cmd(t_addres *addres, t_pipe_exec *tmp, \
char **env, int (*fds)[2], int i)
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
	run_cmd(addres, tmp, env);
	exit(0);
}

void	child_proc(t_addres *addres, t_pipe_exec *tmp, \
char **env, int (*fds)[2], int i)
{
	sig_main(2);
	if (i == 0)
		first_cmd(addres, tmp, env, fds, i);
	else if (i < addres->pipe_count)
		needle_cmd(addres, tmp, env, fds, i);
	else
		last_cmd(addres, tmp, env, fds, i);
}

void	get_sig(t_addres *addres, int *pid)
{
	int	i;

	i = -1;
	while (++i <= addres->pipe_count)
	{
		waitpid(pid[i], &addres->exit_status, 0);
		if (WIFEXITED(addres->exit_status))
			;
		else if (WIFSIGNALED(addres->exit_status))
		{
			if (addres->exit_status == SIGQUIT && i == addres->pipe_count + 1)
				write(1, ":Quit 3\n", 8);
			else if (addres->exit_status == SIGINT \
			&& i == addres->pipe_count + 1)
				write(1, "\n", 1);
			addres->exit_status += 128;
		}
	}
}

void	multi_piping(t_addres *addres, char **env, int (*fds)[2], int *pid)
{
	t_pipe_exec	*tmp;
	int			i;

	i = -1;
	tmp = addres->pipe_list;
	while (++i <= addres->pipe_count)
	{
		sig_main(1);
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
}

void	pipe_execution(t_addres *addres, char **env)
{
	int			*pid;
	int			(*fds)[2];
	int			i;

	i = -1;
	fds = malloc(sizeof(int *) * addres->pipe_count);
	if (!fds)
		return ;
	pid = (int *)malloc(sizeof(int) * (addres->pipe_count + 1));
	if (!pid)
		return ;
	set_pipelist(addres);
	open_infile(&addres->pipe_list);
	while (++i < addres->pipe_count)
		pipe(fds[i]);
	multi_piping(addres, env, fds, pid);
	get_sig(addres, pid);
	free(fds);
	free(pid);
}
