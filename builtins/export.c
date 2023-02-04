/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:40:29 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/02/04 14:59:28 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->flag == 0)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->key, 1);
			ft_putchar_fd('=', 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putchar_fd('"', 1);
			ft_putchar_fd('\n', 1);
		}
		tmp = tmp->next;
	}
}

char	*fill_key(char *str)
{
	char	*key;
	int		len;

	len = lenght_until(str, '=');
	key = (char *)malloc(sizeof(char) * (len + 1));
	key[len] = '\0';
	ft_memmove(key, str, len);
	return (key);
}

char	*fill_value(char *str)
{
	char	*value;
	int		len;
	int		lenstr;

	value = NULL;
	lenstr = ft_strlen(str);
	len = lenstr - lenght_until(str, '=') - 1;
	value = (char *)malloc(sizeof(char) * (len + 1));
	value[len] = '\0';
	while (--len >= 0)
		value[len] = str[--lenstr];
	return (value);
}

void	export_value(t_env **env, char **cmd)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while (cmd && cmd[i])
	{
		key = fill_key(cmd[i]);
		if (!env_key_handling(key))
		{
			value = fill_value(cmd[i]);
			if (change_value(env, key, value) == -1)
				append_env(env, key, value, 0);
			else
				free(key);
		}
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("':	not a valid identifier\n", 2);
			free(key);
		}
		i++;
	}	
}

void	export(t_env **env, char **cmd)
{
	int		i;

	i = 0;
	if (cmd && !cmd[++i])
		print_export(*env);
	else
		export_value(env, cmd);
}
