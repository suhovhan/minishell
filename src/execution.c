/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:04:41 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/19 19:56:17 by suhovhan         ###   ########.fr       */
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
}
