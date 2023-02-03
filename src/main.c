/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:36 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 18:48:42 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	a(void)
{
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_addres		addres;
	struct termios	def;
	char			*get_line;
	char			*get_line_tmp;
	char			**environment;

	(void)ac;
	(void)av;
	addres.std_out_copy = dup(1);
	addres.std_input_copy = dup(0);
	rl_catch_signals = 0;
	addres.exit_status = 0;
	setup_env(&(addres.env), env);
	rl_event_hook = a;
	if (tcgetattr(0, &def) < 0)
		perror("minishell: signal_error1");
	while (1)
	{
		g_status = 0;
		if (tcsetattr(0, TCSANOW, &def) < 0)
			printf("minishell: signal_error2\n");
		sig_main(0);
		get_line = readline("minishell-$ ");
		get_line_tmp = get_line;
		if (get_line && *get_line)
			add_history(get_line);
		if (!get_line)
		{
			ft_putstr_fd("exit\n", 1);
			exit(addres.exit_status);
		}
		if (check_quotes(get_line))
		{
			free(get_line);
			continue ;
		}
		append_addres(&addres, &get_line_tmp);
		clean_backslash(&addres.token);
		if (check_pipe(addres.token) == -1)
		{
			free(get_line);
			free_token(&(addres.token));
			continue ;
		}
		if (heredoc(&addres) == -1)
		{
			print_syntax_error(1);
			free(get_line);
			free_addres(&addres);
			continue ;
		}
		if (check_redirections(addres.token) == -1)
		{
			free(get_line);
			free_token(&(addres.token));
			continue ;
		}
		pars_expression(&addres);
		redirect_input(&addres);
		run_redirections(&addres);
		clean_space_from_token(&(addres.token));
		environment = list_to_char(&addres);
		execution(&addres, environment);
		if (g_status)
			addres.exit_status = g_status;
		change_value(&(addres.env), "?", ft_itoa(addres.exit_status));
		free_mtx(environment);
		free(get_line);
		get_line = NULL;
		free_addres(&addres);
	}
	return (0);
}
