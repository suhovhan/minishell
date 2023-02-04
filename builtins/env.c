/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:56:25 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/02/04 18:01:10 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		ft_putstr_fd(env[i], 1);
		write(1, "\n", 1);
	}
}

int	list_size(t_env *env)
{
	int	count;

	count = 0;
	if (!env)
		return (0);
	while (env)
	{
		if (env->flag == 0)
			count++;
		env = env->next;
	}
	return (count);
}

char	**list_to_char(t_addres *address)
{
	t_env	*temp;
	char	**envp;
	int		i;
	char	*ptr;

	envp = malloc(sizeof(char **) * (list_size(address->env) + 1));
	i = 0;
	temp = address->env;
	while (temp)
	{
		if (temp->flag == 0)
		{
			envp[i] = ft_strjoin(temp->key, "=");
			ptr = envp[i];
			envp[i] = ft_strjoin(envp[i], temp->value);
			free(ptr);
			i++;
		}
		temp = temp->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	env_handling(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (ft_strcmp(s[i], "env") != 0)
			return (i);
	}
	return (-1);
}

void	ft_env(char **line, t_addres *cmd)
{
	int		i;
	char	**env;
	t_env	*temp;
	char	**get_line;

	i = 0;
	temp = cmd->env;
	get_line = line;
	if (env_handling(get_line) != -1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(get_line[env_handling(get_line)], 2);
		perror(": ");
		cmd->exit_status = 127;
	}
	else if (env_handling(get_line) == -1)
	{
		env = list_to_char(cmd);
		print_env(env);
		free_mtx(env);
		cmd->exit_status = 0;
	}
	temp = temp->next;
}
