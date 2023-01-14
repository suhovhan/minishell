/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetrosy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:15:59 by mpetrosy          #+#    #+#             */
/*   Updated: 2022/12/22 16:47:16 by mpetrosy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_utils.c"
#include "builtin.h"
#include "minishell_structs.h"

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

/*
int	main()
{
	char	*s;

	// s = "sss5A./5gc";
	// s = "/_Agc";
	 s = "..";
	// s = "ABC";
	printf("%d\n", unset_handling(s));
	return (0);
}
*/

void	remove_node(t_env *list, char *key)
{
	t_env	*temp;

	temp = list;
	while (temp->next)
	{
		temp->key = NULL;
		temp->value = NULL;
		if (ft_strcmp(temp->next->key, key) == 0)
			temp->next = temp->next->next;
	}
}

// void	unset(char *cmd)
// {
// 	char	**get_line;
// 	t_env	*arg;

// 	get_line = ft_split(cmd, ' ');
// 	while(arg)
// 	{
// 		if (ft_strcmp(//get_line[0], "unset") == 0 && //unset_handling(get_line[1] == 1))
// 			remove_node(/*(t_env *)get_line[1]*/arg, get_line[1]);
// 		else
// 			printf("minishell: unset: `%s': not a valid identifier", get_line[1]);	
// 	}	

// }