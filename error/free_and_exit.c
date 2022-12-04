/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:41:50 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/04 02:44:53 by suhovhan         ###   ########.fr       */
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

int	free_pars(t_pars *pars)
{
	int	i;

	i = -1;
	while ((*pars).cmd_line[++i])
		free((*pars).cmd_line[i]);
	free((*pars).cmd_line);
	return (0);
}

int	free_addres(t_addres *addres)
{
	free_separators(&(*addres).sep);
	free_redirection(&(*addres).redir);
	free_pars(&(*addres).pars);
	return (0);
}
