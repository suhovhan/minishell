/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:58:10 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/10 22:43:50 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	exit(0);
	return (0);
}
