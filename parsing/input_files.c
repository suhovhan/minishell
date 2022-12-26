/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 01:51:01 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/26 06:02:18 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_input(t_addres *addres)
{
	t_token	*tmp;
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
			addres->descriptor_input = open_red_in(tmp->token);
			index = tmp->index;
			addres->input_file = ft_strdup(tmp->token);
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
		dup2(0, fd);
	close(fd);
	return (fd);
}
