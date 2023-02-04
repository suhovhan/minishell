/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:41:38 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/04 14:42:00 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	a(void)
{
	return (0);
}

void	set_term_attr(int flag)
{
	struct termios	termios_p;

	tcgetattr(0, &termios_p);
	if (flag == 0)
	{
		termios_p.c_lflag &= ~ECHOCTL;
		tcsetattr(0, 0, &termios_p);
	}
	else if (flag == 1)
	{
		termios_p.c_lflag |= ECHOCTL;
		tcsetattr(0, 0, &termios_p);
	}
}

void	ft_ctrl_c(int signum)
{
	(void)signum;
	rl_done = 1;
	g_status = 1;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
}

void	sig_main(int flag)
{
	if (flag == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_ctrl_c);
	}
	if (flag == 1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
	if (flag == 2)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	if (flag == 3)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
	}
}
