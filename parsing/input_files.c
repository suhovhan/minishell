/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 01:51:01 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 17:25:22 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	input_helper(t_addres *addres, t_token **tmp, int pipe_index)
{
	int		descriptor;
	int		index;

	index = (*tmp)->index;
	(*tmp) = (*tmp)->next;
	remove_node_from_token(&(addres->token), index);
	if ((*tmp)->type == _SPACE)
	{
		index = (*tmp)->index;
		(*tmp) = (*tmp)->next;
		remove_node_from_token(&(addres->token), index);
	}
	index = (*tmp)->index;
	descriptor = open((*tmp)->token, O_RDONLY);
	if (descriptor == -1)
		addres->exit_status = \
		print_no_such_file_or_directory((*tmp)->token);
	if (!addres->infile || index > addres->infile->input_index)
		add_infile(addres, ft_strdup((*tmp)->token), \
		pipe_index, (*tmp)->index);
	close(addres->descriptor_input);
	(*tmp) = (*tmp)->next;
	remove_node_from_token(&(addres->token), index);
}

void	redirect_input(t_addres *addres)
{
	t_token	*tmp;
	int		pipe_index;

	pipe_index = 0;
	tmp = addres->token;
	while (tmp)
	{
		if (tmp->type == _PIPE)
			pipe_index++;
		if (tmp->type == _RED_IN)
			input_helper(addres, &tmp, pipe_index);
		else
			tmp = tmp->next;
	}
}
