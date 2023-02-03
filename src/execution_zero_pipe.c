/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_zero_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:40:01 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 16:41:33 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execution(t_addres *addres, char **env)
{
	if (addres->pipe_count == 0)
		exec_zeropipe(addres, env);
	else if (addres->pipe_count > 0)
		pipe_execution(addres, env);
}

void	parent_proc_zero_pipe(t_addres *addres, int pid)
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

void	child_proc_zero_pipe(t_addres *addres, char **env)
{
	int		pid;
	char	**path;
	char	*cmd;

	path = NULL;
	cmd = 0;
	sig_main(1);
	pid = fork();
	if (pid)
		parent_proc_zero_pipe(addres, pid);
	else
	{
		sig_main(2);
		path = env_path(addres->env);
		cmd = ft_strdup(addres->cmd_line[0]);
		addres->cmd_line[0] = check_path(addres->cmd_line[0], path, 0);
		execve(addres->cmd_line[0], addres->cmd_line, env);
		check_path(cmd, path, 1);
	}
}

void	exec_zeropipe(t_addres *addres, char **env)
{
	addres->cmd_line = cmd_line(addres->token);
	if (addres->infile)
	{
		addres->descriptor_input = open(addres->infile->filename, O_RDONLY);
		dup2(addres->descriptor_input, 0);
	}
	if (addres->descriptor_output[0])
		dup2(addres->descriptor_output[0], 1);
	close(addres->descriptor_input);
	close(addres->descriptor_output[0]);
	if (isbuiltin(addres->cmd_line, addres) == -1)
		child_proc_zero_pipe(addres, env);
	dup2(addres->std_out_copy, 1);
	dup2(addres->std_input_copy, 0);
	free_mtx(addres->cmd_line);
}
