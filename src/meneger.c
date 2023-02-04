/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meneger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:37:08 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/04 17:22:03 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	main_loop(t_addres *addres, struct termios def)
{
	char			*get_line;

	while (1)
	{
		g_status = 0;
		if (tcsetattr(0, TCSANOW, &def) < 0)
			perror("minishell: ");
		sig_main(0);
		get_line = readline("minishell-$ ");
		if (g_status == 1)
		{
			addres->exit_status = g_status;
			change_value(&(addres->env), "?", ft_itoa(addres->exit_status));
			continue ;
		}
		if (parser(addres, &get_line) == -1)
			continue ;
		set_term_attr(1);
		main_execution(addres);
		free_addres(addres);
	}
}

int	main_tokenize(t_addres *addres, char *get_line)
{
	char			*get_line_tmp;

	get_line_tmp = get_line;
	if (!get_line)
	{
		ft_putstr_fd("exit\n", 1);
		exit(addres->exit_status);
	}
	if (check_quotes(get_line))
		return (-1);
	append_addres(addres, &get_line_tmp);
	clean_backslash(&addres->token);
	if (check_pipe(addres->token) == -1)
	{
		free_token(&(addres->token));
		return (-1);
	}
	return (0);
}

int	main_redirect(t_addres *addres)
{
	if (heredoc(addres) == -1)
	{
		print_syntax_error(1);
		free_addres(addres);
		return (-1);
	}
	if (check_redirections(addres->token) == -1)
	{
		free_token(&(addres->token));
		return (-1);
	}
	pars_expression(addres);
	redirect_input(addres);
	run_redirections(addres);
	clean_space_from_token(&(addres->token));
	return (0);
}

void	main_execution(t_addres *addres)
{
	char			**environment;

	environment = list_to_char(addres);
	execution(addres, environment);
	if (g_status)
		addres->exit_status = g_status;
	change_value(&(addres->env), "?", ft_itoa(addres->exit_status));
	free_mtx(environment);
}
