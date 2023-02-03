/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:04:41 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 18:30:32 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
