/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:56:25 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/01/15 15:14:09 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_env(t_addres *addres)
{
	t_env	*temp;

	temp = addres->env;
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	return (0);
}
/*
int ft_env(char *line, t_addres cmd)
{
	t_env	*temp;
	char	**get_line;
	int		i;

	temp = cmd.env;
	get_line = ft_split(line, ' ');
	i = -1;
	temp = cmd.env;
	while (temp)
	{
		if (ft_strcmp(get_line[++i], "env") == 0 && ft_strcmp(get_line[1], "env") != 0)
		{
			printf("env: %s: No such file or directory\n", get_line[1]);
			cmd.exit_status = 127;
		}
		while (ft_strcmp(get_line[++i], "env") == 0)
		{
			printf("%s=%s\n", temp->key, temp->value);
			cmd.exit_status = 0;
		}
		temp = temp->next;
	}
	return (0);
}
*/
/*
int	main()
{
	char		*get_line;
	t_addres	exit_status;

	while (1)
	{
		get_line = readline("minishell-$ ");
		if (!get_line)
			return (0);
		ft_env(get_line, exit_status);
		printf("XX\n");
		add_history(get_line);
	}
	return (0);
}*/

/*
void	env(char *line, t_addres cmd, t_env *env)
{
	t_env	*temp;
	char	**get_line;
	int		i;

	temp = env;
	get_line = ft_split(line, ' ');
	i = 0;
	while (temp)
	{
		if (ft_strcmp(get_line[i], "env") == 0)
		{
			printf("%s=%s\n", temp->key, temp->value);
			cmd.exit_status = 0;
		}
		else
		{
			printf("env: %s: No such file or directory\n", get_line[1]);
			cmd.exit_status = 127;
		}
		temp = temp->next;
	}
}
*/
