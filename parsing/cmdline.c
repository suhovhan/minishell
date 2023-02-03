/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 05:14:07 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 18:32:33 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_arg(t_token **token)
{
	char	*path;
	char	*ptr;

	while (*token && (*token)->type == _SPACE)
		*token = (*token)->next;
	if (*token && (*token)->type == _EXTERNAL)
	{
		path = ft_strdup((*token)->token);
		*token = (*token)->next;
	}
	while (*token && (*token)->type == _EXTERNAL)
	{
		ptr = path;
		path = ft_strjoin(ptr, (*token)->token);
		free(ptr);
		ptr = NULL;
		*token = (*token)->next;
	}
	return (path);
}

char	**cmd_line(t_token *token)
{
	int		count;
	int		i;
	char	**cmd_line;
	t_token	*tmp;

	tmp = token;
	count = 0;
	i = -1;
	while (token && token->type != _PIPE)
	{
		if (token && token->type == _EXTERNAL)
		{
			while (token && token->type == _EXTERNAL)
				token = token->next;
			count++;
		}
		if (token && token->type != _PIPE)
			token = token->next;
	}
	cmd_line = (char **)malloc(sizeof(char *) * (count + 1));
	while (++i < count)
		cmd_line[i] = get_arg(&tmp);
	cmd_line[i] = 0;
	return (cmd_line);
}

char	**env_path(t_env *env)
{
	char	**env_path;
	char	*ptr;
	int		i;

	i = -1;
	env_path = NULL;
	while (env)
	{
		if (!ft_strcmp(env->key, "PATH"))
		{
			env_path = ft_split(env->value, ':');
			while (env_path[++i])
			{
				ptr = env_path[i];
				env_path[i] = ft_strjoin(env_path[i], "/");
				free(ptr);
				ptr = NULL;
			}
			break ;
		}
		env = env->next;
	}
	return (env_path);
}

char	*my_strchr(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != c)
		;
	if (str[i] != '\0')
		return (str);
	return (0);
}

int	check_backslash(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '/')
		i++;
	if (str[i] == '\0')
		return (0);
	return (-1);
}
