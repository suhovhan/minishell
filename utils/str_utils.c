/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:39 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/04 02:51:54 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	append_sep(t_separators **separators, int sep)
{
	t_separators	*new_node;
	t_separators *last_node;

	new_node = malloc(sizeof(t_separators));
	new_node->sep = sep;
	new_node->next = NULL;
	if (*separators == NULL)
		*separators = new_node;
	else
	{
		last_node = *separators;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	return (0);
}

int	append_redir(t_redirection **redir, char *delimiter, int type)
{
	t_redirection	*new_node;
	t_redirection	*last_node;

	new_node = malloc(sizeof(t_redirection));
	new_node->type = type;
	new_node->delimiter = delimiter;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (*redir == NULL)
		*redir = new_node;
	else
	{
		last_node = *redir;
		while ((*redir)->next != NULL)
			*redir = (*redir)->next;
		(*redir)->next = new_node;
		(*redir)->next->prev = *redir;
		*redir = last_node;
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
