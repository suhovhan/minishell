/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:15 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/21 16:07:17 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/signal.h>
# include <signal.h>

# include "libft.h"
# include "minishell_structs.h"

//lexical analize functions


void	set_token(t_token **token, char **get_line);
int		fill_spaces(char **get_line, t_token **token);
int		fill_redirections(char **get_line, t_token **token);
void	fill_external(char **get_line, t_token **token);
int		fill_quotes_external(char **get_line, t_token **token, int quote);
void	fill_expression(char **get_line, t_token **token);
void	append_addres(t_addres *addres, char **get_line);
char	*search_infile(t_filename *head, int pipe_index);
void	set_pipelist(t_addres *addres);
void	open_infile(t_pipe_exec **pipelist);

//error functions


int		print_syntax_error(int c);
void	exit_shell(t_addres *addres, int	exit_code);
void	free_addres(t_addres *addres);
int		free_token(t_token **token);
int		free_filename(t_filename **filename);
int		free_pipeexec(t_pipe_exec **pipelist);
int		free_env(t_env **env);
void	free_mtx(char **mtx);
int		check_single_quotes(char **get_line);
int		check_duble_quotes(char **get_line);
int		check_quotes(char *get_line);
int		check_heredoc(t_addres *addres);
int		check_syntax(t_token *token);
int		check_pipe(t_token *token);
int		check_redirections(t_token *token);
void	print_no_such_file_or_directory();


//parsing functions


char	*get_arg(t_token **token);
// char	*cmd_args(t_token **token);
char	**cmd_line(t_token *token);
char	**env_path(t_env *env);
char	*check_path(char *str, char **env_path);
char	*get_heredoc_del(char *name, int index);
void	add_infile(t_addres *addres, char *filename, int index, int input_index);
void	add_outfile(t_addres *addres, char *filename, int index, int input_index);
int		heredoc(t_addres *addres);
char	*run_heredoc(t_addres *addres, char *token, int type, int index);
int		run_heredoc_external(t_env *env, char *token, int descriptor);
int		run_heredoc_expansion(char *token, int descriptor);
char	*open_expression_in_line(t_env *env, char *str);
void	pars_expression(t_addres *addres);
void	redirect_input(t_addres *addres);
int		open_red_in(char *filename);
void	run_redirections(t_addres *addres);
int		open_red_out(char *filename);
int		open_red_append(char *filename);

//bulitines functions


int		isbuiltin(char **cmd_line, t_addres *status);
int		no_newline(char *s);
void	echo(char **cmd);
int		is_digit(char **str);
void	ft_exit(char *line, t_addres cmd);
void	pwd(char	*cmd);
void 	ft_env(char *line, t_addres *cmd);


//utils functions


int		append_token(t_token **token, int type, char *str);
int		append_env(t_env **env, char *key, char *value);
int		append_filename(t_filename **head, char *str, int pipe_index, int input_index);
int		append_pipeexec(t_pipe_exec **pipe_list, char **cmd_line, char *infile, int out);
void	remove_node_from_token(t_token **token, int index);
void	clean_space_from_token(t_token	**token);
void	set_env(t_env **env, char **envp);
char 	*find_value_env(t_env	*env, char *key);
char	*fill_word(char **get_line, char ch, int flag);
int		word_len(char *get_line, char ch);
char	*ft_cleanline(char *get_line);
char	**ft_smart_split(char *s);
char	*fillword(char *s, int start_index, int len);
int		getwordcount(char *s, char c);
char	*epur_str(char *str);
// char	*env_path(char **env, char *pathname);
char	**get_env(char	*env);
int		get_wordlen_expression(char **heredoc);
int		get_wordlen_expression(char **heredoc);
char	*execute_expression(char **heredoc);


//
void	pipe_execution(t_addres *addres, char **env);
void	execution(t_addres *addres, char **env);
void	p_mtx(char **str);
void	jogenq_incha(t_env *env, char *heredoc);
int		is_alpha(char *str);
void	cd(char *line, t_env *env);
char	**list_to_char(t_addres *address);
int		list_size(t_env *env);
//


#endif
