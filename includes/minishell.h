/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:15 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/20 03:06:46 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

# include "libft.h"
# include "minishell_structs.h"

//lexical analize functions


void	set_token(char **get_line, t_token **token);
int		fill_spaces(char **get_line, t_token **token);
int		fill_redirections(char **get_line, t_token **token);
void	fill_external(char **get_line, t_token **token);
int		fill_quotes_external(char **get_line, t_token **token, int quote);
void	fill_expression(char **get_line, t_token **token);


//error functions


int		print_syntax_error(int c);
void	exit_shell(t_addres *addres, int	exit_code);
int		free_token(t_token **token);
int		free_env(t_env **env);
int		check_single_quotes(char **get_line);
int		check_duble_quotes(char **get_line);
int		check_quotes(char *get_line);
int		check_heredoc(t_addres *addres);
int		check_syntax(t_token *token);
int		check_pipe(t_token *token);
int		check_redirections(t_token *token);
void	print_no_such_file_or_directory();


//parsing functions


int		heredoc(t_addres *addres);
void	run_heredoc(t_addres *addres, char *token, int type);
int		run_heredoc_external(t_env *env, char *token, int descriptor);
int		run_heredoc_expansion(char *token, int descriptor);
char	*open_expression_in_line(t_env *env, char *str);
void	pars_expression(t_addres *addres);
void	redirect_input(t_addres *addres);
int		open_red_in(char *filename);
void	run_redirections(t_addres *addres);
int		open_red_out(char *filename);
int		open_red_append(char *filename);

//utils functions


int		append_token(t_token **token, int sep, char *str);
int		append_env(t_env **env, char *key, char *value);
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
char	*env_path(char **env, char *pathname);
char	**get_env(char	*env);
int		get_wordlen_expression(char **heredoc);
int		get_wordlen_expression(char **heredoc);
char	*execute_expression(char **heredoc);


//


void	p_mtx(char **str);
void	jogenq_incha(t_env *env, char *heredoc);


//


#endif
