/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:36 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/15 15:20:30 by suhovhan         ###   ########.fr       */
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

// int ft_env(t_addres *addres)
// {
// 	t_env	*temp;

// 	temp = addres->env;
// 	while (temp)
// 	{
// 		printf("%s=%s\n", temp->key, temp->value);
// 		temp = temp->next;
// 	}
// 	return (0);
// }

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_addres	addres;
	char		*get_line;
	char		*get_line_tmp;

	int std_out_copy = dup(1);
	int std_input_copy = dup(0);
	// int	pid;
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
		ft_env(get_line, &addres);
	//	ft_exit(get_line, addres);
		//p_mtx(list_to_char(&addres));                   
// add child process here
		// t_token *tmp = addres.token;
		// while (tmp)
		// {
		// 	printf("index = %d\ttype = %d\ttoken = %s\n", tmp->index, tmp->type, tmp->token);
		// 	tmp = tmp->next;
		// }
		if (heredoc(&addres) == -1)
		{
			free_token(&(addres.token));
			continue;
		}
		if (check_syntax(addres.token) == -1)
		{
			free_token(&(addres.token));
			continue;
		}
		pars_expression(&addres);
		redirect_input(&addres);
		run_redirections(&addres);
		clean_space_from_token(&(addres.token));
		addres.cmd_line = get_cmdline(&addres);
		addres.descriptor_input = open(addres.input_filename, O_RDONLY);
		dup2(addres.descriptor_input, 0);
		close(addres.descriptor_input);
		// if (isbuiltin(addres.cmd_line, &addres) == -1)
		// {
		// 	pid = fork();
		// 	if (pid)
		// 		wait(&pid);
		// 	else
		// 	{
		// 		execve(addres.cmd_line[0], addres.cmd_line, env);
		// 		return (127);
		// 	}
		// }
		dup2(std_out_copy, 1);
		dup2(std_input_copy, 0);
		free(get_line);
		free_mtx((addres.cmd_line));
		free_token(&(addres.token));
	}
	free_env(&(addres.env));
	return (0);
}
