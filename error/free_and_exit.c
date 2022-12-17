/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:41:50 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/15 21:09:34 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_token(t_token **token)
{
	t_token *tmp;

	while (*token)
	{
		tmp = *token;
		(*token) = (*token)->next;
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
