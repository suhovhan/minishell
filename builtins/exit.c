/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:32:49 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/02/02 16:48:42 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == 43 || str[i] == 45)
		i++;
	if (!str[i])
		return (-1);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i])
		return (-1);
	return (0);
}

void	num_req(char *line, t_addres *cmd)
{
	if (ft_strcmp(line, "9223372036854775807") > 0)
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", line);
		cmd->exit_status = 255;
		exit (cmd->exit_status);
	}
}

int	ft_abs(long double n)
{
	if (n < 0)
		n *= (-1);
	return (n);
}

void	ft_exit(char **line, t_addres *cmd)
{
	if (!line[1])
	{
		printf("exit\n");
		exit(cmd->exit_status);
	}
	else if (is_digit(line[1]) == 0 && !line[2])
	{
		num_req(line[1], cmd);
		if (line[1][0] != '-' || line[1][0] == '+')
			cmd->exit_status = ft_atoi(line[1]) % 256;
		else
			cmd->exit_status = 256 - ft_abs(ft_atoi(line[1]) % 256);
	}
	else if (line[2])
	{
		printf("minishell: exit: too many arguments\n");
		cmd->exit_status = 1;
		return ;
	}
	num_req(line[1], cmd);
	change_value(&(cmd->env), "?", ft_itoa(cmd->exit_status));
	exit (cmd->exit_status);
}
