/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_expression.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:41:17 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/15 14:20:04 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>

char	*open_expression_in_line(t_env *env, char *str)
{
	char	*new_line;
	char	*ptr;
	char	*expressed_line;
	char	*ret;

	new_line = ft_strdup("\0");
	while(str && *str)
		if (str && *str && *str == '$')
		{
			expressed_line = execute_expression(&str);
			ptr = expressed_line;
			if (ft_strcmp(expressed_line, "(null)") != 0)
			{
				if (ft_strlen(expressed_line) == 0)
					expressed_line = ft_strdup("$");
				else
					expressed_line = find_value_env(env, ptr);
				if (ptr && *ptr)
					free(ptr);
				ptr = new_line;
				if (expressed_line && *expressed_line)
				{
					if (!new_line || !*new_line)
						new_line = ft_strdup(expressed_line);
					else
						new_line = ft_strjoin(new_line, expressed_line);
					free(expressed_line);
				}
				if (ptr && *ptr)
					free(ptr);	
			}
			else
				str++;
		}
		else
		{
			ptr = new_line;
			ret = NULL;
			ret = malloc(sizeof(char) * 2);
			ret[0] = *str;
			ret[1] = '\0';
			if (!new_line || !*new_line)
				new_line = ft_strdup(ret);
			else
				new_line = ft_strjoin(new_line, ret);
			if (ptr && *ptr)
				free(ptr);
			free(ret);
			str++;
		}
	return (new_line);
}

void	pars_expression(t_addres *addres)
{
	t_token	*tmp;
	char	*ptr;
	
	tmp = addres->token;
	while (tmp)
	{
		if (tmp->type == _EXTERNAL || tmp->type == _EXPANSION_DUBLE)
		{
			ptr = tmp->token;
			tmp->token = open_expression_in_line(addres->env, ptr);
			tmp->type = _EXTERNAL;
			free(ptr);
			ptr = NULL;
		}
		else if (tmp->type == _EXPANSION_SINGLE)
			tmp->type = _EXTERNAL;
		tmp = tmp->next;
	}
}
