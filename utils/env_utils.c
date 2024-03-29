/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:03:31 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 13:33:06 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*env_get_key(char *env)
{
	int		i;
	int		j;
	char	*key;

	i = -1;
	j = -1;
	while (env[++i] != '=')
		;
	key = malloc(sizeof(char) * (i + 2));
	i = -1;
	while (env[++i] != '=')
		key[++j] = env[i];
	key[++j] = '\0';
	return (key);
}

char	*env_get_value(char *env)
{
	int		i;
	int		j;
	int		lenght;
	char	*value;

	i = -1;
	j = -1;
	lenght = 0;
	while (env[++i] != '=')
		;
	while (env[++i])
		lenght++;
	value = malloc(sizeof(char) * lenght + 1);
	i = -1;
	while (env[++i] != '=')
		;
	while (env[++i])
		value[++j] = env[i];
	value[++j] = '\0';
	return (value);
}

char	**get_env(char	*env)
{
	char	**split_env;

	split_env = malloc(sizeof(split_env) * 3);
	split_env[0] = env_get_key(env);
	split_env[1] = env_get_value(env);
	split_env[2] = NULL;
	return (split_env);
}

void	set_env(t_env **env, char **envp)
{
	int		i;
	int		j;
	char	**split_env;

	i = -1;
	while (envp[++i])
	{
		j = -1;
		split_env = get_env(envp[i]);
		append_env(env, ft_strdup(split_env[0]), ft_strdup(split_env[1]), 0);
		while (split_env[++j])
		{
			free(split_env[j]);
			split_env[j] = NULL;
		}
		free(split_env);
		split_env = NULL;
	}
}

int	change_value(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	int		i;

	tmp = *env;
	i = -1;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			i = 0;
			free(tmp->value);
			tmp->value = value;
			break ;
		}
		tmp = tmp->next;
	}
	return (i);
}
