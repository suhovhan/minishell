/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:47:29 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/01/15 15:39:48 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	go_home(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, "HOME") == 0)
			chdir(temp->value);
		else if (!ft_strcmp(temp->key, "HOME"))
			printf("minishell: cd: HOME not set");   // check when unset is ready
		temp = temp->next;
	}
}

void	go_to(char *cmd, char *cur_path)
{
	char	*go_to_path;
	t_env	*temp;
	t_env	*env = NULL;

	go_to_path = getcwd(&cmd[0], 1000);
	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, "PWD") == 0)
			temp->value = go_to_path;
		else if (ft_strcmp(temp->key, "OLDPWD") == 0)
			temp->value = cur_path;
		temp = temp->next;
	}
}

void	cd(char *line, t_env *env/*, t_addres cmd*/)
{
	char	**get_line;
	char	path[1024];
	char	*old_pwd;

	get_line = ft_split(line, ' ');
	old_pwd = getcwd(path, sizeof(path));
	if (!get_line || !get_line[0] || ft_strcmp(get_line[0], "~") == 0)
	{
		go_home(env);
	//	cmd.exit_status = 0;
	}
	else if (get_line[0])
	{
		if (chdir(get_line[0]) == -1)
			printf("minishell: cd: %s: No such file or directory\n", get_line[0]);
		else
			go_to(ft_strdup("usr/bin/cd"), get_line[0]);
	}
}
