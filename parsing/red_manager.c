/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:43:03 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/17 23:46:45 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_redirections(t_addres *addres)
{
	t_token	*tmp;
	t_token	*ptr;
	int		descriptor;
	
	tmp = addres->token;
	ptr = addres->token;
	descriptor = 0;
	while (tmp)
	{
		if (tmp && tmp->type == _RED_IN)
			descriptor = run_red_in(&ptr, tmp->index);
		// else if (tmp && tmp->type == _RED_OUT)
		// {
		// 	descriptor = run_red_out(&ptr, tmp->index);
		// 	tmp = ptr;	
		// }
		// else if (tmp && tmp->type == _APPEND)
		// {
		// 	descriptor = run_red_append(&ptr, tmp->index);
		// 	tmp = ptr;
		// }
		tmp = tmp->next;
	}
	addres->descriptor = descriptor;
}

int	run_red_in(t_token **token, int index)
{
	int		descriptor;
	int		rem_node_index;
	t_token	*tmp;
	t_token	*ptr;;

	tmp = *token;
	ptr = *token;
	descriptor = 0;
	while (tmp && tmp->index != index)
		tmp = tmp->next;
	if (tmp && tmp->index == index)
	{
		rem_node_index = tmp->index;
		tmp = tmp->next;
		remove_node_from_token(&ptr, rem_node_index);
		if (tmp->type == _EXTERNAL)
		{
			descriptor = open_red_in(tmp->token);
			rem_node_index = tmp->index;
			tmp = tmp->next;
			remove_node_from_token(&ptr, rem_node_index);
		}
	}
	*token = ptr;
	return (descriptor);
}

// int	run_red_out(t_token **token, int index)
// {
// 	int		descriptor;
	
	
// 	return (descriptor);
// }

// int	run_red_append(t_token **token, int index)
// {
// 	int		descriptor;
	
	
// 	return (descriptor);
// }
