/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:20:42 by suhovhan          #+#    #+#             */
/*   Updated: 2022/11/24 16:33:49 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tokenization(t_pars	**parser, t_separators *sep, char **get_line)
{
	t_redirection	*redir;
	t_token 		*token;
	char			**splited_token;
	char			*get_line_tmp;
	(void)parser;

	token = NULL;
	redir = NULL;
	splited_token = ft_split(*get_line, '|');
	get_line_tmp = *get_line;
	set_redirection(sep, &redir, &get_line_tmp);
	get_line_tmp = ft_cleanline(*get_line);
	append_token(&token, &redir, get_line_tmp);
	return (0);
}
