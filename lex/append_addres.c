/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_addres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 01:57:26 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/21 20:15:52 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	append_addres(t_addres *addres, char **get_line)
{
	t_env	*env_tmp;
	t_token	*token_tmp;
	
	set_token(&(addres->token), get_line);
	token_tmp = addres->token;
	env_tmp = addres->env;
	addres->pipe_count = 0;
	addres->exit_status = 0;
	addres->descriptor_input = -1;
	while (env_tmp)
	{
		if (!ft_strcmp(env_tmp->key, "SHLVL"))
			addres->shlvl = ft_atoi(env_tmp->value);
		env_tmp = env_tmp->next;
	}
	while (token_tmp)
	{
		if (token_tmp->type == _PIPE)
			addres->pipe_count++;	
		token_tmp = token_tmp->next;	
	}
	addres->descriptor_output = (int*)malloc(sizeof(int) * (addres->pipe_count + 1));
	int i = -1;
	while (++i <= addres->pipe_count)
	{
		addres->descriptor_output[i] = -1;
		append_filename(&addres->infile, NULL, i, -1);
	}
}
