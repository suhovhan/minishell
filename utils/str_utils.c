/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:39 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 13:31:59 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	word_len(char *get_line, char ch)
{
	int	len;

	len = 0;
	get_line++;
	while (get_line && *get_line && *get_line != ch)
	{
		len++;
		get_line++;
	}
	return (len);
}

char	*fill_word(char **get_line, char ch, int flag)
{
	char	*res;
	int		i;

	i = -1;
	res = (char *)malloc(sizeof(char) * (word_len(*get_line, ch) + 1));
	if (flag == 0)
	{
		while (**get_line != ch)
		{
			res[++i] = **get_line;
			(*get_line)++;
		}
	}
	else
	{	
		while (get_line && *get_line && **get_line && **get_line != ch \
		&& **get_line != '<' && **get_line != '>' && **get_line != '|')
		{	
			res[++i] = **get_line;
			(*get_line)++;
		}
	}
	res[++i] = '\0';
	return (res);
}

char	*ft_cleanline(char *get_line)
{
	int		i;
	char	*res;
	char	*end;

	i = -1;
	res = (char *)malloc(sizeof(char) * ft_strlen(get_line));
	while (*get_line != '\0')
	{
		if (*get_line > 31 && *get_line < 127)
			res[++i] = *get_line;
		get_line++;
	}
	res[++i] = '\0';
	end = (char *)malloc(sizeof(char) * ft_strlen(res));
	ft_strlcpy(end, res, ft_strlen(res) + 1);
	free(res);
	res = NULL;
	return (end);
}

char	*find_value_env(t_env	*env, char *key)
{
	char	*value;

	value = NULL;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			value = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	return (value);
}
