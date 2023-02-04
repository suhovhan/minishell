/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:05:23 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/02/04 17:16:30 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	new_line(char **s, int *res)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (s[i])
	{
		j = 0;
		if (s[i][j] == '-' && s[i][j + 1] == 'n')
		{
			j++;
			while (s[i][j] == 'n')
				j++;
			if (s[i][j] != '\0')
				break ;
		}
		else
			break ;
		i++;
	}
	*res = i - 1;
	return (0);
}

void	echo(char **cmd)
{
	int		i;
	char	**get_line;

	i = 1;
	get_line = cmd;
	if (!get_line[1])
		ft_putchar_fd('\n', 1);
	if (get_line[1] && get_line[1][0] == '-' && new_line(get_line, &i) == 0)
	{
		while (get_line[++i])
		{
			ft_putstr_fd(get_line[i], 1);
			if (get_line[i + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	else if (get_line[1])
	{
		i = 0;
		while (get_line[++i])
			ft_putstr_fd(get_line[i], 1);
		ft_putchar_fd('\n', 1);
	}
}
