/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:39 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/14 16:59:43 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	append_token(t_token **token, int type, char *str)
{
	static int	index = -1;
	t_token		*new_node;
	t_token 	*last_node;

	if (*str == '\0')
		return (0);
	new_node = malloc(sizeof(t_token));
	new_node->type = type;
	new_node->index = ++index;
	new_node->token = str;
	new_node->next = NULL;
	if (*token == NULL)
	{
		index = -1;
		new_node->index = ++index;
		*token = new_node;
	}
	else
	{
		last_node = *token;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	return (0);
}

int	remove_node_from_token(t_token **token, int index)
{
	t_token	*tmp;
	t_token	*ptr;

	tmp = *token;
	if (index == 0)
	{
		ptr = tmp->next;
		free(tmp);
		tmp = NULL;
		*token = ptr;
		return (0);
	}
	while (tmp && tmp->index + 1 < index)
		tmp = tmp->next;
	ptr = tmp;
	if (tmp && tmp->next)
	{
		tmp = tmp->next;
		if (tmp->index == index)
			ptr->next = tmp->next;
		free(tmp);
		tmp = NULL;
	}
	return (0);
}

int	append_env(t_env **env, char *key, char *value)
{
	t_env	*new_node;
	t_env	*last_node;

	new_node = malloc(sizeof(t_env));
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (*env == NULL)
		*env = new_node;
	else
	{
		last_node = *env;
		while ((*env)->next != NULL)
			*env = (*env)->next;
		(*env)->next = new_node;
		*env = last_node;
	}
	return (0);
}

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
		(*get_line)++;
		while (**get_line != ch)
		{
			res[++i] = **get_line;
			(*get_line)++;
		}
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
		res = malloc(sizeof(char) * len + 1);
	}
	while (heredoc && *heredoc && **heredoc &&\
	((**heredoc >= 'a' && **heredoc <= 'z') || \
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
