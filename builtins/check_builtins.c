/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:58:10 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/28 02:58:11 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	isbuiltin(char **cmd_line, t_addres status, t_env *env)
{
	if (!cmd_line)
		return (0);
	if (cmd_line[0] && !ft_strcmp(cmd_line[0], "/bin/echo"))
		echo(*cmd_line);
	else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "/bin/pwd"))
		pwd(*cmd_line);
	else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "/bin/cd"))
		cd(*cmd_line[1], env);
	// else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "export"))
	// 	export(cmd_line[1]);
	// else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "unset"))
	// 	unset(cmd_line[1]);
	else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "/bin/exit"))
		ft_exit(cmd_line[1], status);
	// else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "env"))
	// 	env(cmd_line[1]);
	else
		return (-1);
	return (0);
}
