/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:42:15 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/04 02:45:03 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "minishell_structs.h"

//lexical analize functions

void	set_sep(char **get_line, t_separators **separators);
int		lexical_analize(char *get_line);
int		tokenization(t_addres *addres, char **get_line);
int		fill_spaces(char **get_line, t_separators **separators);
int		fill_redirections(char **get_line, t_separators **separators);
int		fill_external(char **get_line, t_separators **separators);
int		fill_quotes_external(char **get_line, t_separators **separators, int quote);
int		set_redir_in(char **get_line, t_redirection **redir);
int		set_redir_out(char **get_line, t_redirection **redir);
int		set_redir_heredoc(char **get_line, t_redirection **redir);
int		set_redir_append(char **get_line, t_redirection **redir);
int		set_redirection(t_separators *sep, t_redirection **redir, char **get_line);

//error functions

int		print_syntax_error(int c);
int		free_separators(t_separators **separators);
int		free_redirection(t_redirection **redirection);
int		free_pars(t_pars *pars);
int		free_addres(t_addres *addres);
int		check_quotes(t_separators *separators);
int		check_pipe(t_separators *separators);
int		check_heredoc(t_separators *separators);
int		check_redirections(t_separators *separators);
int		check_part_of_sep(t_separators *separators);
int		check_separators(t_separators *separators);

//utils functions

char	*fill_word(char **get_line, char ch, int flag);
int		word_len(char *get_line, char ch);
int		append_sep(t_separators **separators, int sep);
int		append_redir(t_redirection **redir, char *delimiter, int type);
char	*ft_cleanline(char *get_line);
char	**ft_smart_split(char *s, char c);
char	*fillword(char *s, int start_index, int len);
int		getwordcount(char *s, char c);
char	*epur_str(char *str);


void	p_mtx(char **str);
#endif
