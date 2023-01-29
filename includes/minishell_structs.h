/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:08 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/29 14:29:32 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef struct s_pipe_execution_structure t_pipe_execution_structure;

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
	int					index;
	int					type;
	char				*token;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct	s_env
{
	int				flag;
	char 			*key;
	char 			*value;
	struct s_env	*next;
}				t_env;

typedef	struct s_filename
{
	int					input_index;
	int					pipe_index;
	char				*filename;
	struct s_filename	*next;
	struct s_filename	*prev;
}				t_filename;

typedef struct s_pipe_exec
{
	char	**cmd_line;
	char	*infile;
	int		fd_infile;
	int		output;
	struct s_pipe_exec	*next;
}				t_pipe_exec;

typedef struct	s_addres
{
	int				exit_status;
	int				descriptor_input;
	int				std_out_copy;
	int 			std_input_copy;
	int				*descriptor_output;
	int				pipe_count;
	int				shlvl;
	char			**cmd_line;
	t_pipe_exec		*pipe_list;
	t_filename		*infile;
	t_env			*env;
	t_token			*token;
}				t_addres;


#endif
