/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:08 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/10 19:24:42 by ergrigor         ###   ########.fr       */
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
	_HEREDOC = 5, // << heredoc
	_APPEND = 6, // >> append
	_EXPANSION_SINGLE = 7, // [ '...' ]
	_EXPANSION_DUBLE = 8, // [ "..." ]
	_DELIMITER = 9, // redirection filename
}			t_types;

typedef	struct s_token
{
	int				index;
	int				type;
	char			*token;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct	s_env
{
	char 			*key;
	char 			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_addres
{
	int			exit_status;
	int			input_index;
	int			descriptor_input;
	int			descriptor_output;
	int			pipe_count;
	int			shlvl;
	char		*input_filename;
	char		**cmd_line;
	t_env		*env;
	t_token		*token;
}				t_addres;

#endif
