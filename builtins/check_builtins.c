/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:58:10 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/26 19:50:43 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	isbuiltin(char **cmd_line, t_addres *status)
{
	if (!cmd_line)
		return (0);
	if (cmd_line[0] && !ft_strcmp(cmd_line[0], "echo"))
		echo(cmd_line);
	else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "pwd"))
		pwd(*cmd_line);
	else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "cd"))
		cd(cmd_line[1], status->env);
	// else if (cmd_line[0] && !ft_strmp(cmd_line[0], "export"))
	// 	export(cmd_line[1]);
	// else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "unset"))
	// 	unset(cmd_line[1]);
	else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "exit"))
	{
		exit(0);
		// ft_exit(cmd_line, *status);
	}
	// else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "env"))
	// 	ft_env(cmd_line[1], status);
	else
		return (-1);
	return (0);
}
