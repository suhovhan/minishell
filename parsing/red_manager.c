/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:43:03 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/27 16:54:15 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_redirections(t_addres *addres)
{
	t_token	*tmp;
	int		descriptor;
	int		pipe_index;
	int		index;
	int		type;

	pipe_index = 0;
	tmp = addres->token;
	while (tmp)
	{
		if (tmp->type == _PIPE)
			pipe_index++;
		if (tmp && (tmp->type == _RED_OUT || tmp->type == _APPEND))
		{
			type = tmp->type;
			tmp = tmp->next;
			remove_node_from_token(&(addres->token), tmp->prev->index);
			if (tmp && tmp->type == _SPACE)
			{
				tmp = tmp->next;
				remove_node_from_token(&(addres->token), tmp->prev->index);
			}
			if (addres->descriptor_output[pipe_index])
				close(addres->descriptor_output[pipe_index]);
			if (type == _RED_OUT)
				addres->descriptor_output[pipe_index] = open_red_out(tmp->token);
			else
				addres->descriptor_output[pipe_index] = open_red_append(tmp->token);
			remove_node_from_token(&(addres->token), tmp->index);
		}
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
				add_infile(addres, ft_strdup(tmp->token), pipe_index, tmp->index);
			close(addres->descriptor_input);
			tmp = tmp->next;
			remove_node_from_token(&(addres->token), index);
		}
		tmp = tmp->next;
	}
}

int	open_red_out(char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		print_no_such_file_or_directory();
	return (fd);
}

int	open_red_append(char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		print_no_such_file_or_directory();
	return (fd);
}
