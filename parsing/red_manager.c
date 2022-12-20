/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:43:03 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/20 05:36:57 by suhovhan         ###   ########.fr       */
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
		if (tmp && (tmp->type == _RED_OUT || tmp->type == _APPEND))
		{
			if (tmp && tmp->type == _RED_OUT)
				addres->descriptor_output = open_red_out(tmp->next->token);
			else if (tmp && tmp->type == _APPEND)
				addres->descriptor_output = open_red_append(tmp->next->token);
			tmp = tmp->next;
			remove_node_from_token(&(addres->token), tmp->prev->index);
			index = tmp->index;
			tmp = tmp->next;
			remove_node_from_token(&(addres->token), index);
		}
		else
			tmp = tmp->next;
	}
	usleep(10);
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
