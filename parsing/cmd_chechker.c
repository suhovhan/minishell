/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_chechker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:32:02 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 18:33:33 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
