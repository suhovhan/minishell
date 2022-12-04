/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:20:42 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/04 04:54:53 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	p_mtx(char **str)
{
	int	i = -1;
	while (str[++i])
		printf("cmd_%d = [%s]\n", i, str[i]);
}

int	tokenization(t_addres *addres, char **get_line)
{
	char			*get_line_tmp;

	(*addres).redir = NULL;
	get_line_tmp = *get_line;
	set_redirection((*addres).sep, &(*addres).redir, &get_line_tmp);
	get_line_tmp = epur_str(ft_cleanline(*get_line));
	addres->pars.cmd_line = ft_split(get_line_tmp, '|');
	free(*get_line);
	return (0);
}
