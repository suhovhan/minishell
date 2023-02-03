/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:27:42 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 18:28:13 by suhovhan         ###   ########.fr       */
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
