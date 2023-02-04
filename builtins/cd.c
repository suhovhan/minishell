/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:47:29 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/02/04 17:49:31 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	go_home(t_env *env)
{
	int		i;
	t_env	*temp;

	temp = env;
	i = 0;
	while (temp)
	{
		if (ft_strcmp(temp->key, "HOME") == 0)
		{
			i = 1;
			change_value(&env, "PWD", ft_strdup(temp->value));
			chdir(temp->value);
		}
		temp = temp->next;
	}
	if (i == 0)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
}

void	go_to(t_env **env)
{
	char	*go_to_path;

	go_to_path = NULL;
	go_to_path = getcwd(go_to_path, 256);
	change_value(env, "PWD", ft_strdup(go_to_path));
	free(go_to_path);
}

void	cd_norm(t_env *env, char **line)
{	
	char	*ptr;
	char	*ptr2;

	change_value(&env, "OLDPWD", find_value_env(env, "PWD"));
	ptr = find_value_env(env, "PWD");
	ptr2 = ft_strjoin(ptr, "/");
	free(ptr);
	ptr = ft_strjoin(ptr2, line[0]);
	free(ptr2);
	change_value(&env, "PWD", ptr);
	ft_putstr_fd("minishell-$", 2);
	ft_putstr_fd(line[0], 2);
	perror(" ");
}

void	pr_error(char *line)
{	
	ft_putstr_fd("minishell-$ ", 2);
	ft_putstr_fd(line, 2);
	perror(" ");
}

void	cd(char *line, t_env *env)
{
	int		chdir_value;
	char	path[1024];
	char	*old_pwd;
	char	**get_line;

	get_line = ft_split(line, ' ');
	old_pwd = getcwd(path, sizeof(path));
	change_flag(&env, "OLDPWD", 0);
	change_value(&env, "OLDPWD", ft_strdup(old_pwd));
	if (!get_line || !get_line[0])
		go_home(env);
	else if (get_line[0])
	{
		chdir_value = chdir(get_line[0]);
		if (chdir_value == -1)
			pr_error(line);
		else if (!chdir_value && !old_pwd)
			cd_norm(env, get_line);
		else
			go_to(&env);
	}
	free_mtx(get_line);
}
