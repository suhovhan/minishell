/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:36 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/20 05:11:36 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	p_mtx(char **mtx)
{
	int	i = -1;
	int	j;
	char	**sp;
	while (mtx[++i])
	{
		j = -1;
		sp = ft_split(mtx[i], '=');
		while (sp[++j])
			printf("%s\n", sp[j]);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	t_addres	addres;
	char		*get_line;
	char		*get_line_tmp;

	set_env(&(addres.env), env);
	t_env	*env_tmp = addres.env;
	while (env_tmp)
	{
		if (!ft_strncmp(env_tmp->key, "SHLVL", 5))
			addres.shlvl = ft_atoi(env_tmp->value);
		env_tmp = env_tmp->next;
	}
	while (1)
	{
		get_line = readline("minishell-$ ");
		get_line_tmp = get_line;
		if (get_line && *get_line)
			add_history(get_line);
		if (!ft_strncmp(get_line, "exit", 4))
		{
			free(get_line);
			exit(0);
		}
		if (check_quotes(get_line))	
			continue;
		get_line_tmp = get_line;
		set_token(&get_line_tmp, &(addres.token));
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
		int std_out_copy = dup(1);
		int std_input_copy = dup(0);
		pars_expression(&addres);
		redirect_input(&addres);
		run_redirections(&addres);
		t_token *tmp = addres.token;
		while (tmp)
		{
			printf("%s\n", tmp->token);
			tmp = tmp->next;
		}
		dup2(std_out_copy, 1);
		dup2(0, std_input_copy);
		free(get_line);
		free_token(&(addres.token));
	}
	free_env(&(addres.env));
	return (0);
}
