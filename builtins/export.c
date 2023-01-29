/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:40:29 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/01/28 17:42:50 by suhovhan         ###   ########.fr       */
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

int		lenght_until(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			break;
		i++;
	}
	return (i);
}

char	*fill_key(char *str)
{
	char	*key;
	int		len;

	len = lenght_until(str, '=');
	key = (char*)malloc(sizeof(char) * (len + 1));
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
	value = (char*)malloc(sizeof(char) * (len + 1));
	value[len] = '\0';
	while (--len >= 0)
		value[len] = str[--lenstr];
	return (value);
}

void	export(t_env **env, char **cmd)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	if (cmd && !cmd[++i])
		print_export(*env);
	else
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
				printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
				free(key);
			}
			i++;
		}
}
