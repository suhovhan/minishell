/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:37:05 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 19:08:19 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*set_newlist(char *line)
{
	t_token	*new_list;
	t_token	*tmp;

	new_list = 0;
	set_token(&new_list, &line);
	tmp = new_list;
	while (tmp)
	{
		tmp->index = -1;
		if (new_list->type == _HEREDOC)
			new_list->type = _EXTERNAL;
		tmp = tmp->next;
	}
	return (new_list);
}

void	setup_needle_list(t_token **token, char *line, int index)
{
	t_token	*new_list;
	t_token	*tmp;
	t_token	*ptr;

	new_list = set_newlist(line);
	tmp = *token;
	while (tmp && tmp->index != index)
		tmp = tmp->next;
	ptr = tmp->next;
	if (tmp->prev)
	{
		tmp->prev->next = new_list;
		new_list->prev = tmp->prev;
	}
	while (new_list->next)
		new_list = new_list->next;
	if (ptr)
	{
		ptr->prev = new_list;
		new_list->next = ptr;
	}
	while (new_list->prev)
		new_list = new_list->prev;
	*token = new_list;
}

int	pars_expression_norm(t_addres *addres, t_token **tmp)
{
	t_token	*last;
	char	*ptr;

	ptr = (*tmp)->token;
	(*tmp)->token = open_expression_in_line(addres->env, ptr);
	if (!(*tmp)->token)
		(*tmp)->token = ft_strdup("");
	else if ((*tmp)->type == _EXTERNAL && ft_strcmp(ptr, (*tmp)->token))
	{
		last = (*tmp)->next;
		setup_needle_list(&(addres->token), (*tmp)->token, (*tmp)->index);
		free((*tmp)->token);
		free((*tmp));
		free(ptr);
		(*tmp) = last;
		return (-1);
	}
	(*tmp)->type = _EXTERNAL;
	free(ptr);
	return (0);
}
