/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:36 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/26 06:59:42 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	p_mtx(char **mtx)
{
	int		i = -1;
	int		j;
	while (mtx[++i])
	{
		j = -1;
		printf("%d = %s\n",i, mtx[i]);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_addres	addres;
	char		*get_line;
	char		*get_line_tmp;

	int std_out_copy = dup(1);
	int std_input_copy = dup(0);
	int	pid;
	while (1)
	{
		get_line = readline("minishell-$ ");
		get_line_tmp = get_line;
		if (get_line && *get_line)
			add_history(get_line);
		else
			continue;
		if (check_quotes(get_line))
			continue;
		append_addres(&addres, &get_line_tmp, env);
// add child process here
		if (check_heredoc(&addres) == -1)	
		{
			free_token(&(addres.token));
			continue;
		}
		heredoc(&addres);
		if (check_syntax(addres.token) == -1)
		{
			free_token(&(addres.token));
			continue;
		}
		pars_expression(&addres);
		redirect_input(&addres);
		run_redirections(&addres);
		clean_space_from_token(&(addres.token));
		// t_token *tmp = addres.token;
		// while (tmp)
		// {
		// 	printf("index = %d\ttype = %d\ttoken = %s\n", tmp->index, tmp->type, tmp->token);
		// 	tmp = tmp->next;
		// }
		addres.cmd_line = get_cmdline(&(addres.token));
		// p_mtx(addres.cmd_line);
		if (isbuiltin(addres.cmd_line) == -1)
		{
			pid = fork();
			if (pid)
				wait(&pid);
			else
			{
				execve(addres.cmd_line[0], addres.cmd_line, env);
				return (127);
			}
		}
		dup2(std_out_copy, 1);
		dup2(0, std_input_copy);
		free(get_line);
		free_mtx((addres.cmd_line));
		free_token(&(addres.token));
	}
	free_env(&(addres.env));
	return (0);
}
