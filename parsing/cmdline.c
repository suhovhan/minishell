/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 05:14:07 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/26 06:20:59 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_pathname(t_token **token)
{
	char	*path;
	char	*str1;
	char	*ptr;
	int		index;
	t_token	*tmp;

	tmp = *token;
	path = "\0";
	if (ft_strncmp(tmp->token, "/bin/", 5))
		path = ft_strjoin(path, "/bin/");
	while (tmp && tmp->type != _SPACE)
	{
		ptr = path;
		str1 = ft_strdup(tmp->token);
		path = ft_strjoin(path, str1);
		free(str1);
		if (*ptr)
			free(ptr);
		index = tmp->index;
		tmp = tmp->next;
		remove_node_from_token(token, index);
	}
	return (path);
}

char	*get_cmdargs(t_token **token)
{
	t_token	*tmp;
	int		index;
	char	*cmd_args;
	char	*ptr;
	
	tmp = *token;
	cmd_args = "\0";
	while (tmp && tmp->type == _SPACE)
		tmp = tmp->next;
	while (tmp && tmp->type != _SPACE)
	{
		ptr = cmd_args;
		cmd_args = ft_strjoin(cmd_args, tmp->token);
		if (*ptr)
			free(ptr);
		index = tmp->index;
		tmp = tmp->next;
		remove_node_from_token(token, index);
	}
	return (cmd_args);
}

char	**get_cmdline(t_token **token)
{
	int		arg_count;
	int		i;
	char	**cmd_line;
	t_token	*tmp;	

	tmp = *token;
	arg_count = 1;
	i = 0;
	while (tmp)
	{
		if (tmp->type == _SPACE)
			arg_count++;
		tmp = tmp->next;
	}
	cmd_line = (char**)malloc(sizeof(char*) * (arg_count + 1));
	cmd_line[i] = get_pathname(token);
	while (++i < arg_count)
		cmd_line[i] = get_cmdargs(token);
	cmd_line[i] = 0;
	return (cmd_line);
}
