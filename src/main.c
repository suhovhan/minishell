/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:36 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/04 02:45:41 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	t_addres	addres;
	char		*get_line;
	char		*get_line_tmp;

	while (1)
		while (1)
		{
			get_line = readline("minishell-$ ");
			addres.redir = NULL;
			add_history(get_line);
			if (!ft_strncmp(get_line, "exit", 4))
				return (0);
			get_line_tmp = get_line;
			set_sep(&get_line_tmp, &(addres.sep));
			if (check_part_of_sep(addres.sep) == -1)	
			{
				free_addres(&addres);
				break ;
			}
			get_line_tmp = get_line;
			tokenization(&addres, &get_line_tmp);
			if (check_separators(addres.sep) == -1)	
			{
				free_addres(&addres);
				break ;
			}
			p_mtx(addres.pars.cmd_line);
			while (addres.redir)
			{
				printf("type = %d\tdel = %s\n", addres.redir->type, addres.redir->delimiter);
				addres.redir = addres.redir->next;
			}
			free_addres(&addres);
		}
	return (0);
}
