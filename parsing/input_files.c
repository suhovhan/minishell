/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 01:51:01 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/29 19:42:08 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_input(t_addres *addres)
{
	t_token	*tmp;
	int		descriptor;
	int		index;
	int		pipe_index;

	pipe_index = 0;
	tmp = addres->token;
	while (tmp)
	{
		if (tmp->type == _PIPE)
			pipe_index++;
		if (tmp->type == _RED_IN)
		{
			index = tmp->index;
			tmp = tmp->next;
			remove_node_from_token(&(addres->token), index);
			if (tmp->type == _SPACE)
			{
				index = tmp->index;
				tmp = tmp->next;
				remove_node_from_token(&(addres->token), index);
			}
			index = tmp->index;
			descriptor = open(tmp->token, O_RDONLY);
			if (descriptor == -1)
				print_no_such_file_or_directory();
			if (!addres->infile || index > addres->infile->input_index)
				add_infile(addres, ft_strdup(tmp->token), \
				pipe_index, tmp->index);
			close(addres->descriptor_input);
			tmp = tmp->next;
			remove_node_from_token(&(addres->token), index);
		}
		else
			tmp = tmp->next;
	}
}
