/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:36 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/14 17:16:42 by suhovhan         ###   ########.fr       */
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

	while (1)
		while (1)
		{
			get_line = readline("minishell-$ ");
			if (get_line && *get_line)
				add_history(get_line);
			if (!ft_strncmp(get_line, "exit", 4))
				return (0);
			get_line_tmp = get_line;
			if (check_quotes(get_line_tmp))	
				break ;
			set_token(&get_line_tmp, &(addres.token));
			if (check_heredoc(addres.token) == -1)	
			{
				free_token(&(addres.token));
				break ;
			}
			set_env(&(addres.env), env);
			heredoc(&addres);
			// t_token *tmp = addres.token;
			// while (tmp)
			// {
			// 	printf("index = %d\ttype = %d\ttoken = %s\n", tmp->index, tmp->type, tmp->token);
			// 	tmp = tmp->next;
			// }
			if (check_syntax(addres.token) == -1)	
			{
				free_token(&(addres.token));
				break ;
			}
			free_token(&(addres.token));
		}
	return (0);
}
