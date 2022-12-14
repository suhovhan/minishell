/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:08 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/14 17:12:38 by suhovhan         ###   ########.fr       */
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
	_EXPANSION_SINGLE = 12, // [ '...' ]
	_EXPANSION_DUBLE = 13, // [ "..." ]
	_DELIMITER = 14, // redirection filename
}			t_types;

typedef	struct s_token
{
	int					index;
	int					type;
	char				*token;
	struct s_token	*next;
}				t_token;

typedef struct	s_env
{
	char 			*key;
	char 			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_addres
{
	int				exit_status;
	int				descriptor;
	int				pipe_count;
	t_env			*env;
	t_token			*token;
}				t_addres;
#endif
