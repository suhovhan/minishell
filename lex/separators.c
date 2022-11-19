#include "../includes/minishell.h"

int	fill_spaces(char **get_line, t_separators **separators)
{
	while (**get_line == ' ')
		(*get_line)++;
	(*get_line)--;
	append(separators, _SPACE);
	return (0);
}

int	fill_redirections(char **get_line, t_separators **separators)
{
	if (**get_line == '<')
	{
		(*get_line)++;
		if (**get_line == '<')
			append(separators, _HEREDOC);
		else
		{
			(*get_line)--;
			append(separators, _RED_IN);
		}
	}
	else if (**get_line == '>')
	{
		(*get_line)++;
		if (**get_line == '>')
			append(separators, _APPEND);
		else
		{
			(*get_line)--;
			append(separators, _RED_OUT);
		}
	}
	return (0);
}

int	fill_external(char **get_line, t_separators **separators)
{
	append(separators, _EXTERNAL);
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

int	set_sep(char *get_line, t_separators **separators)
{
	while (*get_line)
	{
		// printf("%c\n", **get_line);
		if (*get_line == ' ')
			fill_spaces(&get_line, separators);
		else if (*get_line == '|')
			append(separators, _PIPE);
		else if (*get_line == '$')
			append(separators, _EXPRESSION);
		else if (*get_line == 39)
			append(separators, _SINGLE_QUOTE);
		else if (*get_line == '"')
			append(separators, _DUBLE_QUOTE);
		else if (*get_line == '<' || *get_line == '>')
			fill_redirections(&get_line, separators);
		else
			fill_external(&get_line, separators);
		get_line++;
	}
	return (0);
}
