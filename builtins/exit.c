/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:32:49 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/01/24 18:16:04 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_digit(char **str)
{
	int	i;
	int	j;

	i = 0;
	if ((str[i][0] != 43 && str[i][0] != 45)
		&& (!(str[i][0] >= 48 && str[i][0] <= 57)))
		return (-1);
	if ((str[i][0] == 43 || str[i][0] == 45) && !str[i][1])
		return (-1);
	j = 1;
	while (str[i][j])
	{
		if (str[i][j] >= 48 && str[i][j] <= 57)
			j++;
		else
			return (-1);
	}
	return (0);
}

void	num_req(char **line, t_addres cmd)
{
	char			**get_line;
	long double		max;

	get_line = line;
	max = 9223372036854775807;
	if (is_digit(&get_line[0]) == -1)
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", get_line[0]);
		cmd.exit_status = 255;
		exit (cmd.exit_status);
	}
	else if ((ft_atoi(get_line[0]) > max
			|| ft_atoi(get_line[0]) < (max * (-1) - 1)))
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", get_line[0]);
		cmd.exit_status = 255;
		pause();
		exit (cmd.exit_status);
	}
}

void	many_args(char **line, t_addres cmd)
{
	char			**get_line;

	get_line = line;
	if (is_digit(&get_line[0]) == 0 && get_line[1])
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		cmd.exit_status = 1;
	}
}

void	ft_exit(char **line, t_addres cmd)
{
	char			**get_line;

	get_line = line;
	num_req(line, cmd);
	if (!get_line || !get_line[0])
	{
		printf("exit\n");
		cmd.exit_status = 0;
	 	exit (cmd.exit_status);
	}
	else if (is_digit(&get_line[0]) == 0 && !get_line[1])
	{
		// printf("%s\n", get_line[0]);
		printf("exit\n");
		cmd.exit_status = ft_atoi(get_line[0]) % 256;
		printf("%d\n", cmd.exit_status);
		exit (cmd.exit_status);
	}
	many_args(line, cmd);
}
