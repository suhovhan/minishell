/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:32:49 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/01/31 14:02:26 by suhovhan         ###   ########.fr       */
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

void	num_req(char **line, t_addres *cmd)
{
	char			**get_line;
	long double		max;

	get_line = line;
	max = 9223372036854775807;
	get_line++;
	if ((is_digit(get_line) == -1) || (ft_atoi(get_line[1]) > max || ft_atoi(get_line[1]) < (max * (-1) - 1)))
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", get_line[0]);
		cmd->exit_status = 255;
		exit (cmd->exit_status);
	}
}

void	many_args(char **line, t_addres *cmd)
{
	char			**get_line;

	get_line = line;
	if (is_digit(&get_line[1]) == 0 && get_line[2])
	{
		printf("minishell: exit: too many arguments\n");
		cmd->exit_status = 1;
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
	num_req(line, cmd);
	change_value(&(cmd->env), "?", ft_itoa(cmd->exit_status));
	exit (cmd->exit_status);
}
