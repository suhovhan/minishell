#include "../includes/minishell_utils.h"

int	append(t_separators **separators, int sep)
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

int	append_token(t_token **token, char *text, int sep)
{
	t_token	*new_node;
	t_token *last_node;

	new_node = malloc(sizeof(t_token));
	new_node->type = sep;
	new_node->token = text;
	new_node->next = NULL;
	if (*token == NULL)
		*token = new_node;
	else
	{
		last_node = *token;
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