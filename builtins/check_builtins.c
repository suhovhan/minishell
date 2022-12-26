#include "../includes/minishell.h"

int	isbuiltin(char **cmd_line)
{
	if (!cmd_line)
		return (0);
	if (cmd_line[0] && !ft_strcmp(cmd_line[0], "/bin/echo"))
		echo(cmd_line);
	else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "/bin/pwd"))
		pwd(*cmd_line);
	// else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "cd"))
	// 	cd(cmd_line[1]);
	// else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "export"))
	// 	export(cmd_line[1]);
	// else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "unset"))
	// 	unset(cmd_line[1]);
	// else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "exit"))
	// 	exit(cmd_line[1]);
	// else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "env"))
	// 	env(cmd_line[1]);
	else
		return (-1);
	return (0);
}
