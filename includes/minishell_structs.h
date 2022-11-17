#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef enum s_types
{
	_external = 0, // text
	_space = 1, // space
	_red_in = 2, // < redirection input
	_red_out = 3, // > redirection output
	_pipe = 4, // | pipe
	_expressions = 5, // $ expressions
	_single_quote = 6, // ' quote
	_duble_quote = 7, // " double qoute
	_heredoc = 8, // << heredoc
	_append = 9, // >> append
}			t_types;

typedef	struct s_token
{
	int				token;
	struct s_token	*next;
}				t_token;

#endif