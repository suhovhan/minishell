#include "../includes/minishell.h"

int	append(t_token **tokend_line, int sep)
{
	t_token	*new_node;
	t_token *last_node;

	new_node = malloc(sizeof(t_token));
	new_node->token = sep;
	new_node->next = NULL;
	if (*tokend_line == NULL)
		*tokend_line = new_node;
	else
	{
		last_node = *tokend_line;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	return (0);
}

int	word_len(char *get_line, char ch)
{
	int	len;

	len = 0;
	get_line++;
	while (*get_line != ch)
	{
		len++;
		get_line++;
	}
	return (len);
}

char	*fill_word(char **get_line, char ch)
{
	char	*res;
	int		i;
	int		len;

	i = -1;
	len = word_len(*get_line, ch);
	res = (char*)malloc(sizeof(char) * len + 1);
	(*get_line)++;
	while (**get_line != ch)
	{
		res[++i] = **get_line;
		(*get_line)++;
	}
	res[++i] = '\0';
	return (res);
}

int	fill_spaces(char **get_line, t_token **tokend_line)
{
	while (**get_line == ' ')
		(*get_line)++;
	(*get_line)--;
	append(tokend_line, _space);
	return (0);
}

int	fill_redirections(char **get_line, t_token **tokend_line)
{
	if (**get_line == '<')
	{
		(*get_line)++;
		if (**get_line == '<')
			append(tokend_line, _heredoc);
		else
		{
			(*get_line)--;
			append(tokend_line, _red_in);
		}
	}
	else if (**get_line == '>')
	{
		(*get_line)++;
		if (**get_line == '>')
			append(tokend_line, _append);
		else
		{
			(*get_line)--;
			append(tokend_line, _red_out);
		}
	}
	return (0);
}

int	fill_external(char **get_line, t_token **tokend_line)
{
	append(tokend_line, _external);
	while (**get_line != '\0' && \
		(**get_line != ' ' && \
		**get_line != '<' && \
		**get_line != '>' && \
		**get_line != '|' && \
		**get_line != '$' && \
		**get_line != 39 && \
		**get_line != '"'))
		(*get_line)++;
	(*get_line)--;
	return (0);
}

int	get_token(char **get_line, t_token **tokend_line)
{
	while (**get_line)
	{
		// printf("%c\n", **get_line);
		if (**get_line == ' ')
			fill_spaces(get_line, tokend_line);
		else if (**get_line == '|')
			append(tokend_line, _pipe);
		else if (**get_line == '$')
			append(tokend_line, _expressions);
		else if (**get_line == 39)
			append(tokend_line, _single_quote);
		else if (**get_line == '"')
			append(tokend_line, _duble_quote);
		else if (**get_line == '<' || **get_line == '>')
			fill_redirections(get_line, tokend_line);
		else
			fill_external(get_line, tokend_line);
		(*get_line)++;
	}
	return (0);
}
