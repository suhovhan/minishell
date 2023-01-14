/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetrosy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:47:29 by mpetrosy          #+#    #+#             */
/*   Updated: 2022/12/15 16:59:29 by mpetrosy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "builtin_utils.c"
#include "builtin.h"
#include "ft_split.c"
#include "../includes/minishell.h"

void	pwd(char	*cmd)
{
	char	cwd[256];

	if (cmd && cmd[0] && getcwd(cwd, sizeof(cwd)) != NULL)
		write(1, cwd, ft_strlen(cwd));
	else
		write(1, "Failed to find current directory", 32);
	write(1, "\n", 1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	go_home(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, "HOME") == 0)
		{
			printf("home = %s\n", temp->value);
			chdir(temp->value);
			printf("%s\n", temp->value);
		}
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

void	cd(char *line, t_env *env)
{
	(void)env;
	char	**get_line;
	char	path[1024];
	char	*old_pwd;

	get_line = ft_split(line, ' ');
	old_pwd = getcwd(path, sizeof(path));
	if (!get_line[0])
		return ;
	else if (ft_strcmp(get_line[0], "cd") == 0 && !get_line[1])
		go_home(env);
	else if (ft_strcmp(get_line[0], "cd") == 0 && get_line[1])
	{
		if (chdir(get_line[1]) == -1)
			printf("minishell: cd: %s: No such file or directory\n", get_line[1]);
		else
			go_to(get_line[0], get_line[1]);
	}
}




int	main(int c, char **v, char **envp)
{
	(void)c;
	(void)v;
	//(void)env;
	char	*get_line;
	t_env	*tab;
	t_addres	addres;

	set_env(&tab, envp);
	while (1)
	{
		get_line = readline("minishell-$ ");
		if (!get_line)
			return (0);
		pwd(get_line);
		cd(get_line, tab);
		add_history(get_line);
	}
	return (0);
}