/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 05:14:07 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/26 19:39:32 by suhovhan         ###   ########.fr       */
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
	t_token *tmp;

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
	cmd_line = (char**)malloc(sizeof(char*) * (count + 1));
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
			break;
		}
		env = env->next;
	}
	return (env_path);
}

char	*check_path(char *str, char **env_path)
{
	int		i;
	char	*path;

	path = str;
	i = -1;
	if(!env_path || !*env_path)
		return (str);
	if (!access(str, F_OK))
		return (str);
	while (env_path[++i])
	{
		str = ft_strjoin(env_path[i], path);
		if (!access(str, F_OK))
		{
			free(path);
			path = NULL;
			return (str);
		}
		else
		{
			free(str);
			str = NULL;
		}
	}
	fprintf(stderr, "minishell: %s: command not found\n", path);
	// there would be a function that have to kill process
	return (NULL);
}
