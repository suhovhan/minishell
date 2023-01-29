/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:56:25 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/01/27 19:57:57 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../includes/minishell.h"

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

	i = 0;
	while (s[i])
	{
		if (ft_strcmp(s[i], "env") != 0)
			return (1);
		else
			break;
		i++;
	}
	return (0);
}

void	shlvl(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, "SHLVL") == 0)
			temp->value++;
		temp = temp->next;
	}
}

void ft_env(char *line, t_addres *cmd)
{
	int		i;
	t_env	*temp;
	char	**get_line;

	i = 0;
	temp = cmd->env;
	get_line = ft_split(line, ' ');
	while (temp)
	{
		if (env_handling(get_line) == 1)
		{
			printf("env: %s: No such file or directory\n", get_line[i]);
			cmd->exit_status = 127;
		}
		if (env_handling(get_line) == 0)
		{	
			printf("%s\n", list_to_char(cmd)[++i]);
			cmd->exit_status = 0;
		}
		temp = temp->next;
	}
}
