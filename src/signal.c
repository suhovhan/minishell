#include "../includes/minishell.h"

void	get_and_set_attr(int flag)
{
	struct termios	ts;

	tcgetattr(STDIN_FILENO, &ts);
	if (flag == 0)
	{
		ts.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &ts);
	}
	else if (flag == 1)
	{
		ts.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &ts);
	}
}

void 	ft_ctrl_c(int signum)
{
	(void)signum;
	rl_done = 1;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
}

void	sig_main(int flag)
{
	// get_and_set_attr(0);

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
