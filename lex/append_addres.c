/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_addres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 01:57:26 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/26 03:25:23 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	append_addres(t_addres *addres, char **get_line, char **env)
{
	t_env	*env_tmp;
	t_token	*token_tmp;
	
	set_env(&(addres->env), env);
	set_token(&(addres->token), get_line);
	token_tmp = addres->token;
	env_tmp = addres->env;
	addres->pipe_count = 0;
	addres->exit_status = 0;
	while (env_tmp)
	{
		if (!ft_strncmp(env_tmp->key, "SHLVL", 5))
			addres->shlvl = ft_atoi(env_tmp->value);
		env_tmp = env_tmp->next;
	}
	while (token_tmp)
	{
		if (token_tmp->type == _PIPE)
			addres->pipe_count++;	
		token_tmp = token_tmp->next;	
	}
}
