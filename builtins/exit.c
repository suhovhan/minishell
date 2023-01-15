/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:32:49 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/01/15 15:21:33 by suhovhan         ###   ########.fr       */
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

int	ft_exit(char *line, t_addres cmd)
{
	char			**get_line;
	long double		max;

	max = 9223372036854775807;
	get_line = ft_split(line, ' ');
	if (!get_line[0])
		return (0);
	else if (!get_line[1])
	{
		printf("exit\n");
		cmd.exit_status = 0;
		exit (cmd.exit_status);
	}
	else if ((ft_atoi(get_line[1]) > max || ft_atoi(get_line[1]) < (max * (-1) - 1)))
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", get_line[1]);
		cmd.exit_status = 255;
		exit (cmd.exit_status);
	}
	else if (is_digit(&get_line[1]) == 0 && !get_line[2])
	{
		printf("exit\n");
		exit (ft_atoi(get_line[1]));
	}
	else if (is_digit(&get_line[1]) == 0 && get_line[2])
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		cmd.exit_status = 1;
	}
	else if (is_digit(&get_line[1]) == -1)
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", get_line[1]);
		cmd.exit_status = 255;
		exit (cmd.exit_status);
	}
	free_mtx(&line);
	return (0);
}

