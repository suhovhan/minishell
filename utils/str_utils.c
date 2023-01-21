/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:39 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/20 14:57:46 by suhovhan         ###   ########.fr       */
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
	res = (char*)malloc(sizeof(char) * (word_len(*get_line, ch) + 2));
	if (flag == 0)
	{
		while (**get_line != ch)
		{
			res[++i] = **get_line;
			(*get_line)++;
		}
		res[++i] = '\0';
	}
	else
		while (**get_line && *get_line && get_line && **get_line != '\0' \
		&& **get_line != ch && **get_line != '<' &&\
		 **get_line != '>' && **get_line != '|')
		{
			res[++i] = **get_line;
			**get_line = _DELIMITER;
			(*get_line)++;
		}
	res[++i] = '\0';
	return (res);
}

char	*epur_str(char *str)
{
	char 	*res;
	char	*end;
	int		i;
	int		j;

	i = -1;
	j = -1;
	res = (char *)malloc(sizeof(char) * ft_strlen(str));
	while (str[++i])
	{
		while (str[i] && str[i] == ' ')
		{
			if (str[i + 1] && str[i + 1] != ' ')
				res[++j] = ' ';
			i++;
		}
		i--;
		while (str[++i] && str[i] != ' ')
			res[++j] = str[i];
		i--;
	}
	res[++j] = '\0';
	end = (char *)malloc(sizeof(char) * ft_strlen(res));
	ft_strlcpy(end, res, ft_strlen(res) + 1);
	free(res);
	return (end);
}

char	*ft_cleanline(char *get_line)
{
	int		i;
	char 	*res;
	char	*end;

	i = -1;
	res = (char*)malloc(sizeof(char) * ft_strlen(get_line));
	while (*get_line != '\0')
	{
		if (*get_line > 31 && *get_line < 127)
			res[++i] = *get_line;
		get_line++;
	}
	res[++i] = '\0';
	end = (char*)malloc(sizeof(char) * ft_strlen(res));
	ft_strlcpy(end, res, ft_strlen(res) + 1);
	free(res);
	return (end);
}

// heredoc utils

int	get_wordlen_expression(char **heredoc)
{
	char	*heredoc_line;
	int		i;

	i = 0;
	heredoc_line = *heredoc;
	if (heredoc_line && *heredoc_line && *heredoc_line >= '0' && *heredoc_line <= '9')
		return (-1);
	while (heredoc_line && *heredoc_line && \
	((*heredoc_line >= 'a' && *heredoc_line <= 'z') || \
	(*heredoc_line >= 'A' && *heredoc_line <= 'Z') || \
	(*heredoc_line >= '0' && *heredoc_line <= '9') || 
	*heredoc_line == '-' || *heredoc_line == '_'))
	{
		heredoc_line++;
		i++;
	}
	return (i);
}

char	*execute_expression(char **heredoc)
{
	char	*res;
	int		len;
	int		i;

	i = -1;
	if (heredoc && *heredoc && **heredoc && **heredoc == '$')
	{
		(*heredoc)++;
		len = get_wordlen_expression(heredoc);
		if (len == -1)
			return ("(null)");
		res = malloc(sizeof(char) * len + 1);
	}
	while (heredoc && *heredoc && **heredoc &&\
	((**heredoc >= 'a' && **heredoc <= 'z') ||\
	(**heredoc >= 'A' && **heredoc <= 'Z') || \
	(**heredoc >= '0' && **heredoc <= '9') || \
	**heredoc == '-' || **heredoc == '_'))
	{
		res[++i] = **heredoc;
		(*heredoc)++;
	}
	res[++i] = '\0';
	return (res);
}

char *find_value_env(t_env	*env, char *key)
{
	char	*value;

	value = NULL;
	while (env)
	{
		if (ft_strlen(env->key) == ft_strlen(key) && \
		!(ft_strncmp(env->key, key, ft_strlen(key))))
		{
			value = ft_strdup(env->value);
			break;
		}
		env = env->next;
	}
	return (value);
}
