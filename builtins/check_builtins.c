/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:58:10 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 17:55:09 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	isbuiltin(char **cmd_line, t_addres *addres)
{
	if (!cmd_line)
		return (0);
	if (cmd_line[0] && !ft_strcmp(cmd_line[0], "echo"))
		echo(cmd_line);
	else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "pwd"))
		pwd(*cmd_line);
	else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "cd"))
		cd(cmd_line[1], addres->env);
	else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "export"))
		export(&addres->env, cmd_line);
	else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "unset"))
		unset(&(addres->env), cmd_line);
	else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "exit"))
		ft_exit(cmd_line, addres);
	else if (cmd_line[0] && !ft_strcmp(cmd_line[0], "env"))
		ft_env(cmd_line[1], addres);
	else
		return (-1);
	return (0);
}
