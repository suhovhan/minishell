/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 05:14:07 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/29 22:38:33 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_path(char *path, t_env *env)
{
	char	**env_path;
	char	*file_path;
	int		i;

	i = -1;
	if (!access(path, F_OK))
		return (ft_strdup(path));
	path = ft_strjoin("/", path);
	while (env)
	{
		if (!ft_strcmp(env->key, "PATH"))
			env_path = ft_split(env->value, ':');
		env = env->next;
	}
	while(env_path && env_path[++i])
	{
		file_path = ft_strjoin(env_path[i], path);
		if (!access(file_path, F_OK))
			return (file_path);
		free(file_path);
	}
	printf("minishell-1.1$: %s: command not found\n", path);
	//exit_child();
	return ("\0");
}

char	*get_pathname(t_token **token, t_env *env)
{
	char	*path;
	char	*str1;
	char	*ptr;
	int		index;
	t_token	*tmp;

	tmp = *token;
	path = "\0";
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
	ptr = check_path(path, env);
	if (path && *path)
		free(path);
	return (ptr);
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
	if (!cmd_args || !*cmd_args)
		return (NULL);
	return (cmd_args);
}

char	**get_cmdline(t_addres *addres)
{
	int		arg_count;
	int		i;
	char	**cmd_line;
	t_token	*tmp;	

	tmp = addres->token;
	if (!tmp)
		return (NULL);
	arg_count = 1;
	i = 0;
	while (tmp)
	{
		if (tmp->type == _SPACE)
			arg_count++;
		tmp = tmp->next;
	}
	cmd_line = (char**)malloc(sizeof(char*) * (arg_count + 1));
	cmd_line[i] = get_pathname(&(addres->token), addres->env);
	while (++i < arg_count)
		cmd_line[i] = get_cmdargs(&(addres->token));
	cmd_line[i] = 0;
	return (cmd_line);
}
