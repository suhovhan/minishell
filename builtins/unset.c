/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:15:59 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/01/15 15:15:52 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unset_handling(char *s)
{
	int	i;

	i = 0;
	if (is_alpha(&s[0]) == 1 || s[0] == '_')
	{
		while (s[i++])
		{
			if ((s[i] >= 48 && s[i] <= 57) || (s[i] >= 65
				&& s[i] <= 90) || (s[i] >= 97 && s[i] <= 122) || s[i] == 95)
				return (1);
		}
	}
	return (0);
}

// void	remove_node(t_env **env, char *key)
// {
// 	t_env	*temp;

// 	temp = *env;
// 	while (temp->next)
// 	{
// 		temp->key = NULL;
// 		temp->value = NULL;
// 		if (ft_strcmp(temp->next->key, key) == 0)
// 		{
// 			temp->next = temp->next->next;
// 			free(temp->key);
// 			free(temp->value);
// 		}
// 	}
// }

// void	unset(char *line, t_addres cmd)
// {
// 	char	**get_line;
// 	t_env	**arg;

// 	get_line = ft_split(line, ' ');
// 	while(arg)
// 	{
// 		if (ft_strcmp(get_line[0], "unset") == 0 && unset_handling(get_line[1] == 1))
// 		{
// 			remove_node(arg, get_line[1]);
// 			cmd.exit_status = 0;
// 		}
// 		else
// 		{
// 			printf("minishell: unset: `%s': not a valid identifier", get_line[1]);
// 			cmd.exit_status = 1;
// 		}

// 	}	

// }
