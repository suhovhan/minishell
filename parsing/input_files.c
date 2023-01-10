/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 01:51:01 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/10 15:53:16 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_input(t_addres *addres)
{
	t_token	*tmp;
	int		descriptor;
	int		index;

	tmp = addres->token;
	while (tmp)
	{
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
			if (index > addres->input_index)
			{
				addres->input_index = index;
				addres->input_filename = ft_strdup(tmp->token);
			}
			close(addres->descriptor_input);
			tmp = tmp->next;
			remove_node_from_token(&(addres->token), index);
		}
		else
			tmp = tmp->next;
	}
}

int	open_red_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_no_such_file_or_directory();
	else
		dup2(fd, 0);
	close(fd);
	return (fd);
}
