/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:36 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/18 00:54:00 by suhovhan         ###   ########.fr       */
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
		while (1)
		{
			get_line = readline("minishell-$ ");
			if (get_line && *get_line)
				add_history(get_line);
			if (!ft_strncmp(get_line, "exit", 4))
			{
				free(get_line);
				exit(0);
			}
			if (check_quotes(get_line))	
				break ;
			get_line_tmp = get_line;
			set_token(&get_line, &(addres.token));
			free(get_line);
			if (check_heredoc(&addres) == -1)	
			{
				free_token(&(addres.token));
				break ;
			}
			heredoc(&addres);
			pars_expression(&addres);
			t_env *tmp = addres.env;
			while (tmp)
			{
				printf("key = %s\tvalue = %s\n", tmp->key, tmp->value);
				tmp = tmp->next;
			}
			// run_redirections(&addres);
			if (check_syntax(addres.token) == -1)	
			{
				free_token(&(addres.token));
				break ;
			}
			free_token(&(addres.token));
		}
	return (0);
}
