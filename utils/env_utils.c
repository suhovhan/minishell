/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:03:31 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/13 21:07:56 by suhovhan         ###   ########.fr       */
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
	// printf("nor print %s\n", env_get_key(env));
	split_env[1] = env_get_value(env);
	split_env[2] = NULL;
	return (split_env);
}

void	set_env(t_env **env, char **envp)
{
	int		i;
	char	**split_env;

	i = -1;
	while (envp[++i])
	{
		split_env = get_env(envp[i]);
		append_env(env, split_env[0], split_env[1]);
	}
}

void	print_env(t_env *env, char **envp)
{
	int	i;
	t_env	*temp;

	i = -1;
	temp = env;
	while (envp[++i])
	{
		printf("%s %s\n", env->key, env->value);

	}
}


// int	main(int ac, char **av, char **envp)
// {
// 	t_env	*env;
// 	//t_env	**temp;

// 	//env = malloc(sizeof(t_env **));
// 	//temp = set_env(env, envp);

// 	print_env(env, envp);
// 	return (0);
// }