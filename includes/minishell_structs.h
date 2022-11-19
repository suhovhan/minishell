#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef enum s_types
{
	_EXTERNAL = 0, // text
	_SPACE = 1, // space
	_RED_IN = 2, // < redirection input
	_RED_OUT = 3, // > redirection output
	_PIPE = 4, // | pipe
	_EXPRESSION = 5, // $ expression
	_SINGLE_QUOTE = 6, // ' quote
	_DUBLE_QUOTE = 7, // " double qoute
	_HEREDOC = 8, // << heredoc
	_APPEND = 9, // >> append
	_UNDEFINED = 10, // ; ` doesn't handle
	_CMD = 11, // comands
	_EXPANSION = 12, // [ '...' ] || [ "..." ]
}			t_types;

typedef	struct s_separators
{
	int					sep;
	struct s_separators	*next;
}				t_separators;

typedef	struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}				t_token;

#endif