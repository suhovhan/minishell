/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:15:59 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/02/04 17:56:28 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_key_handling(char *s)
{
	int	i;

	i = -1;
	if (s && *s && (*s == '_' || (*s >= 'a' && *s <= 'z') || \
	(*s >= 'A' && *s <= 'Z')))
	{	
		while (s && s[++i])
			if (!(s[i] == '_' || (s[i] >= 'a' && s[i] <= 'z') || \
			(s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9')))
				return (-1);
	}
	else
		return (-1);
	return (0);
}

void	remove_needle_node(t_env **tmp, char *key)
{
	t_env	*ptr;

	while (tmp && *tmp)
	{
		ptr = (*tmp);
		(*tmp) = (*tmp)->next;
		if ((*tmp) && !ft_strcmp((*tmp)->key, key) && (*tmp)->flag == 0)
		{
			ptr->next = (*tmp)->next;
			free((*tmp)->key);
			free((*tmp)->value);
			free((*tmp));
			break ;
		}
	}
}

void	remove_node(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = *env;
	if (!ft_strcmp(tmp->key, key) && tmp->flag == 0)
	{
		*env = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	else
		remove_needle_node(&tmp, key);
}

void	unset(t_addres *addres, t_env **env, char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[++i])
	{
		if (env_key_handling(cmd[i]) == 0)
			remove_node(env, cmd[i]);
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd[i], 2);
			perror("': ");
			addres->exit_status = 1;
		}
	}
}
