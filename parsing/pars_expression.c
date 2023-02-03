/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_expression.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:41:17 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 19:10:09 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*line_width_expression(t_env *env, char **str)
{
	char	*expressed_line;
	char	*ptr;

	expressed_line = NULL;
	ptr = NULL;
	if (str && *str && **str && **str == '$')
	{
		expressed_line = execute_expression(str);
		ptr = expressed_line;
		if (ft_strcmp(expressed_line, "(null)") != 0)
		{
			if (ft_strlen(expressed_line) == 0)
				expressed_line = ft_strdup("$");
			else
				expressed_line = find_value_env(env, ptr);
		}
		else
		{
			(*str)++;
			return (NULL);
		}
		if (ptr)
			free(ptr);
	}
	return (expressed_line);
}

char	*line_widthout_expression(char **str)
{
	char	*ret;
	char	*ptr;
	char	*tmp;

	ptr = NULL;
	ret = NULL;
	while (str && *str && **str && **str != '$')
	{
		ptr = (char *)malloc(sizeof(char) * 2);
		ptr[0] = **str;
		ptr[1] = '\0';
		if (!ret)
			ret = ft_strdup(ptr);
		else
		{
			tmp = ret;
			ret = ft_strjoin(ret, ptr);
			free(tmp);
		}
		free(ptr);
		(*str)++;
	}
	return (ret);
}

void	norm_expression_line(char **ptr, char **tmp, char **ret)
{
	*ret = NULL;
	*ptr = NULL;
	*tmp = NULL;
}

char	*open_expression_in_line(t_env *env, char *str)
{
	char	*ptr;
	char	*tmp;
	char	*ret;

	norm_expression_line(&ptr, &tmp, &ret);
	while (str && *str)
	{
		if (*str == '$')
			ptr = line_width_expression(env, &str);
		else
			ptr = line_widthout_expression(&str);
		if (!ret)
			ret = ft_strdup(ptr);
		else
		{
			tmp = ret;
			if (!ptr)
				ret = ft_strdup(ptr);
			else
				ret = ft_strjoin(ret, ptr);
			free(tmp);
		}
		free(ptr);
	}
	return (ret);
}

void	pars_expression(t_addres *addres)
{
	t_token	*tmp;

	tmp = addres->token;
	while (tmp)
	{
		if (tmp->type == _EXTERNAL || tmp->type == _EXPANSION_DUBLE)
		{
			if (pars_expression_norm(addres, &tmp) == -1)
				continue ;
		}
		else if (tmp->type == _EXPANSION_SINGLE)
			tmp->type = _EXTERNAL;
		tmp = tmp->next;
	}
}
