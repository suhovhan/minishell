/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:36 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/25 19:29:32 by suhovhan         ###   ########.fr       */
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
		printf("%d = [%s]\n",i, mtx[i]);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_addres	addres;
	char		*get_line;
	char		*get_line_tmp;
	addres.std_out_copy = dup(1);
	addres.std_input_copy = dup(0);
	set_env(&(addres.env), env);
	while (1)
	{
		get_line = readline("minishell-$ ");
		get_line_tmp = get_line;
		if (get_line && *get_line)
			add_history(get_line);
		else
			continue;
		if (check_quotes(get_line))
		{
			free(get_line);
			continue;
		}
		append_addres(&addres, &get_line_tmp);
		clean_backslash(&addres.token);
		// t_token	*tmp = addres.token;
		// while (tmp)
		// {
		// 	printf("index = %d\ttype = %d\ttoken = %s\n", tmp->index, tmp->type, tmp->token);
		// 	tmp = tmp->next;
		// }
		if (check_pipe(addres.token) == -1 || heredoc(&addres) == -1 || check_redirections(addres.token) == -1)
		{
			free(get_line);
			free_token(&(addres.token));
			continue;
		}
		pars_expression(&addres);
		redirect_input(&addres);
		run_redirections(&addres);
		clean_space_from_token(&(addres.token));
		execution(&addres, env);
		free(get_line);
		get_line = NULL;
		free_addres(&addres);
	}
	free_env(&(addres.env));
	return (0);
}
