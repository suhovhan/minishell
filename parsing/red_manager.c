/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:43:03 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/28 04:27:42 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_redirections(t_addres *addres)
{
	t_token	*tmp;
	int		index;
	
	tmp = addres->token;
	while (tmp)
	{
		if (tmp && tmp->type == _RED_OUT)
		{
			tmp = tmp->next;
			remove_node_from_token(&(addres->token), tmp->prev->index);
			if (tmp && tmp->type == _SPACE)
			{
				tmp = tmp->next;
				remove_node_from_token(&(addres->token), tmp->prev->index);
			}
			addres->descriptor_output = open_red_out(tmp->token);
			index = tmp->index;
			tmp = tmp->next;
			remove_node_from_token(&(addres->token), index);
		}
		else if (tmp && tmp->type == _APPEND)
		{
			tmp = tmp->next;
			remove_node_from_token(&(addres->token), tmp->prev->index);
			if (tmp && tmp->type == _SPACE)
			{
				tmp = tmp->next;
				remove_node_from_token(&(addres->token), tmp->prev->index);
			}
			addres->descriptor_output = open_red_append(tmp->token);
			index = tmp->index;
			tmp = tmp->next;
			remove_node_from_token(&(addres->token), index);
		}
		else
			tmp = tmp->next;
	}
}

int	open_red_out(char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		print_no_such_file_or_directory();
	dup2(fd, 1);
	close(fd);
	return (fd);
}

int	open_red_append(char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		print_no_such_file_or_directory();
	dup2(fd, 1);
	close(fd);
	return (fd);
}
