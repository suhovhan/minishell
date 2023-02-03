/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:43:03 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 19:00:12 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	red_meneger_norm(t_addres *addres, t_token **tmp, int pipe_index)
{
	int		type;
	int		index;

	type = (*tmp)->type;
	(*tmp) = (*tmp)->next;
	remove_node_from_token(&(addres->token), (*tmp)->prev->index);
	if ((*tmp) && (*tmp)->type == _SPACE)
	{
		(*tmp) = (*tmp)->next;
		remove_node_from_token(&(addres->token), (*tmp)->prev->index);
	}
	index = (*tmp)->index;
	if (addres->descriptor_output[pipe_index])
		close(addres->descriptor_output[pipe_index]);
	if (type == _RED_OUT)
		addres->descriptor_output[pipe_index] = \
		open_red_out((*tmp)->token);
	else
		addres->descriptor_output[pipe_index] = \
		open_red_append((*tmp)->token);
	remove_node_from_token(&(addres->token), index);
}

void	run_redirections(t_addres *addres)
{
	t_token	*tmp;
	int		pipe_index;

	pipe_index = 0;
	tmp = addres->token;
	while (tmp)
	{
		if (tmp->type == _PIPE)
			pipe_index++;
		if (tmp && (tmp->type == _RED_OUT || tmp->type == _APPEND))
			red_meneger_norm(addres, &tmp, pipe_index);
		tmp = tmp->next;
	}
}

int	open_red_out(char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		print_no_such_file_or_directory(filename);
	return (fd);
}

int	open_red_append(char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		print_no_such_file_or_directory(filename);
	return (fd);
}
