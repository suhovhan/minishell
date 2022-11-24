/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:36 by suhovhan          #+#    #+#             */
/*   Updated: 2022/11/24 16:07:23 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_separators		*separators;
	t_redirection		*redir;
	t_token 			*token;

	char		*get_line;
	char		*get_line_tmp;
	while (1)
		while (1)
		{
			token = NULL;
			redir = NULL;
			get_line = readline("minishell-$ ");
			get_line_tmp = get_line;
			add_history(get_line);
			if (!ft_strncmp(get_line, "exit", 4))
				return (0);
			set_sep(&get_line_tmp, &separators);
			get_line_tmp = get_line;
			if (check_separators(separators) == -1)	
			{
				free_separators(&separators);
				break ;
			}
			set_redirection(separators, &redir, &get_line_tmp);
			get_line_tmp = ft_cleanline(get_line);
			append_token(&token, &redir, get_line_tmp);
			free_token(&token);
			free_separators(&separators);
		}
	return (0);
}
