/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:41:50 by suhovhan          #+#    #+#             */
/*   Updated: 2022/11/24 15:12:46 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_separators(t_separators **separators)
{
	t_separators *sep;
	
	while (*separators)
	{
		sep = *separators;
		(*separators) = (*separators)->next;
		free(sep);
	}
	return (0);
}

int	free_redirection(t_redirection **redirection)
{
	t_redirection *redir;
	
	while (*redirection)
	{
		redir = *redirection;
		(*redirection) = (*redirection)->next;
		free(redir);
	}
	return (0);
}

int	free_token(t_token **token)
{
	t_token *token_tmp;

	while (*token)
	{
		token_tmp = *token;
		(*token) = (*token)->next;
		free_redirection(&(token_tmp)->redir);
		free(token_tmp);
	}
	return (0);
}
