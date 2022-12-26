/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:32:49 by mpetrosy          #+#    #+#             */
/*   Updated: 2022/12/21 21:35:42 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_digit(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] >= 48 || av[i][j] <= 57)
				printf("bash: exit: g: numeric argument required\n");
				return (1);
			j++;
		}
		i++;
	}	
	return (0);
}


int	ft_exit(char *line)
{
	// int						ac;
	int						i;
	char					**get_line;
	long long int			min;
	unsigned long long int	max;

	i = 2;
	max = 9223372036854775807;
	min = -922337203685477580L;
	get_line = ft_split(line, ' ');
	if (ft_strcmp(get_line[0], "exit") == 0 && !get_line[1])
	{	
		printf("exit\n");
		exit (0);
	}
	else if (ft_strcmp(get_line[0], "exit") == 0 && get_line[1] && !get_line[2])
	{
		printf("bash: exit: %s: numeric argument required\n", get_line[1]);
		exit (ft_atoi(get_line[1]));
	}
	else if (ft_strcmp(get_line[0], "exit") == 0 && get_line[1] && get_line[2])
	{
		printf("exit\n");
		printf("bash: exit: too many arguments\n");
		exit (0);
	}
	if (ft_strcmp(get_line[0], "exit") == 0 && !get_line[1])
	{
		printf("exit\n");
		printf("exit\n");
		exit (0);
	}
	// if (get_line[0] && is_digit(ac, &get_line[1]))
	// {
	// 	printf("exit\n");
	// 	exit (0);
	// }
	// if (line[0] && !is_digit(ac, &get_line[1]))
	// {
	// 	printf("exit\n");
	// 	printf("bash: exit: ggg: numeric argument required\n");
	// 	exit (0);
	// }
	if (line[0] && ((unsigned long long)ft_atoi(&line[1]) > max || ft_atoi(&line[1]) < min))
	{
		printf("exit\n");
		printf("bash: exit: ggg: numeric argument required\n");
		exit (255);
	}
	return (0);
}

