/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 05:14:07 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/02 18:58:30 by suhovhan         ###   ########.fr       */
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

void	norm_check_cmd(char *str)
{
	if ((opendir(str) && my_strchr(str, '/') != 0) \
	|| (check_backslash(str) == 0 && ft_strlen(str) != 0))
	{
		ft_putstr_fd("minishell-$: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	if (access(str, F_OK) == 0 && access(str, X_OK) != 0)
	{
		ft_putstr_fd("minishell-$: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	if (opendir(str) == 0 && my_strchr(str, '/') != 0)
	{
		ft_putstr_fd("minishell-$: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
}

void	check_cmd(char *str, char **path)
{
	norm_check_cmd(str);
	if (!path)
	{
		ft_putstr_fd("minishell-$: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
	ft_putstr_fd("minishell-$: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

char	*check_path(char *str, char **env_path, int flag)
{
	int		i;
	char	*path;

	path = 0;
	i = -1;
	if (flag == 1)
		check_cmd(str, env_path);
	while (env_path && env_path[++i])
	{
		path = ft_strjoin(env_path[i], str);
		if (!access(path, F_OK))
			return (path);
	}
	if (!access(str, F_OK))
		return (str);
	return (NULL);
}
