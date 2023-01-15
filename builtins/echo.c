/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:05:23 by mpetrosy          #+#    #+#             */
/*   Updated: 2022/12/26 10:40:15 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	no_newline(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (ft_strcmp(s, "-n") == 0)
		return (1);
	return (0);
}

void	echo(char **cmd)
{
	int	i;
	char	**get_line;

	i = 1;
	get_line = cmd;
	if (!get_line[1])
		printf("\n");
	if (get_line[1] && ft_strcmp(get_line[1], "-n") == 0)
	{
		while (get_line[++i])
		{
			printf("%s", get_line[i]);      // \n ?? \\\\\\?
			if (get_line[i + 1])
				printf(" ");
		}
	}
	i = 0;
	if (get_line[1])
	{
		while (get_line[++i])
			printf("%s ", get_line[i]);      
		printf("\n");
	}
}

