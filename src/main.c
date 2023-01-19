/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:36 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/19 21:16:29 by suhovhan         ###   ########.fr       */
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
	addres.std_out_copy = dup(1);
	addres.std_input_copy = dup(0);
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

		if (check_pipe(addres.token) == -1 || heredoc(&addres) == -1 || check_redirections(addres.token) == -1)
		{
			free_token(&(addres.token));
			continue;
		}
		pars_expression(&addres);
		redirect_input(&addres);
		run_redirections(&addres);
		clean_space_from_token(&(addres.token));

		// t_filename *tmp = addres.infile;
		// while (tmp)
		// {
		// 	printf("index = %d\tinp_index = %d\ttoken = %s\n", tmp->index, tmp->input_index, tmp->filename);
		// 	tmp = tmp->next;
		// }

		execution(&addres, env);
		free(get_line);
		free_token(&(addres.token));
		free_filename(&(addres.infile));
	}
	free_env(&(addres.env));
	return (0);
}
