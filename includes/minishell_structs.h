/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:08 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/04 00:14:29 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	_DELIMITER = 14, // redirection filename
}			t_types;

typedef	struct s_separators
{
	int					sep;
	struct s_separators	*next;
}				t_separators;

typedef	struct s_redirection
{
	int						type;
	char					*delimiter;
	struct s_redirection	*next;
	struct s_redirection	*prev;
}				t_redirection;

typedef struct s_pars
{
	int				count_heredoc;
	int				count_pipe;
	char			**cmd_line;
	t_redirection	*redir;
	t_separators	*separat;
}				t_pars;

typedef struct	s_addres
{
	t_pars			pars;
	t_separators	*sep;
	t_redirection	*redir;
}				t_addres;
#endif
