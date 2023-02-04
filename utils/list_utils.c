/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:50:47 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/04 15:29:01 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_node_from_token(t_token **token, int index)
{
	t_token	*tmp;

	tmp = *token;
	if ((*token)->index == index)
		tmp = (*token)->next;
	while ((*token)->index != index)
		(*token) = (*token)->next;
	if ((*token)->index == index && !(*token)->prev && !(*token)->next)
	{
		free((*token)->token);
		free((*token));
	}
	else if ((*token)->index == index)
	{
		if ((*token)->prev)
			(*token)->prev->next = (*token)->next;
		if ((*token)->next)
			(*token)->next->prev = (*token)->prev;
		free((*token)->token);
		free((*token));
	}
	*token = tmp;
}

void	clean_space_from_token(t_token	**token)
{
	t_token	*tmp;
	int		index;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == _SPACE)
		{
			index = tmp->index;
			tmp = tmp->next;
			if (tmp && tmp->type == _SPACE)
				remove_node_from_token(token, index);
		}
		else
			tmp = tmp->next;
	}
}

void	clean_backslash(t_token	**token)
{
	t_token	*tmp;
	int		index;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == _EXPANSION_SINGLE || tmp->type == _EXPANSION_DUBLE)
		{
			if (!tmp->token || !(*tmp->token))
			{
				index = tmp->index;
				tmp = tmp->next;
				if (tmp && tmp->type != _SPACE && tmp->type != _PIPE)
					remove_node_from_token(token, index);
			}
			else
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}

void	change_flag(t_env **env, char *key, int flag)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			tmp->flag = flag;
			break ;
		}
		tmp = tmp->next;
	}
}

void	setup_env(t_env **env, char **envp)
{
	char	*shlvl;
	int		lvl;

	set_env(env, envp);
	shlvl = find_value_env(*env, "SHLVL");
	lvl = ft_atoi(shlvl) + 1;
	if (lvl == 1000)
		lvl = 0;
	else if (lvl > 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(lvl, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		lvl = 1;
	}
	free(shlvl);
	shlvl = ft_itoa(lvl);
	change_value(env, "SHLVL", shlvl);
	change_flag(env, "OLDPWD", -1);
	append_env(env, ft_strdup("?"), ft_strdup("0"), -1);
}
