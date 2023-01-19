/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:41:50 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/16 14:07:14 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_token(t_token **token)
{
	t_token *tmp;

	if (!token || !*token)
		return (0);
	while (*token)
	{
		tmp = *token;
		(*token) = (*token)->next;
		free(tmp->token);
		free(tmp);
	}
	return (0);
}

int	free_filename(t_filename **filename)
{
	t_filename *tmp;

	if (!filename || !*filename)
		return (0);
	while (*filename)
	{
		tmp = *filename;
		(*filename) = (*filename)->next;
		free(tmp->filename);
		free(tmp);
	}
	return (0);
}

int	free_env(t_env **env)
{
	t_env *tmp;

	if (!env || !*env)
		return (0);
	while (*env)
	{
		tmp = *env;
		(*env) = (*env)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	return (0);
}

void	exit_shell(t_addres *addres, int	exit_code)
{
	if (exit_code == _HEREDOC)
		printf("minishell: maximum here-document count exceeded\n");
	addres->exit_status = 2;
	addres->shlvl--;
	free_token(&addres->token);
	exit(addres->exit_status);
}

void	free_mtx(char **mtx)
{
	int	i;

	i = -1;
	if (mtx)
	{
		while (mtx[++i] && mtx[i][0])
			free(mtx[i]);
		free(mtx);
	}
}
