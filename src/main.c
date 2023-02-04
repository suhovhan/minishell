/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:36 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/04 14:40:57 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	struct termios	def;
	t_addres		addres;

	(void)ac;
	(void)av;
	addres.env = NULL;
	addres.token = NULL;
	addres.infile = NULL;
	addres.pipe_list = NULL;
	set_term_attr(0);
	addres.exit_status = 0;
	setup_env(&(addres.env), env);
	rl_event_hook = a;
	if (tcgetattr(0, &def) < 0)
		perror("minishell: signal_error1");
	main_loop(&addres, def);
	return (0);
}
