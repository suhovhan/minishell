#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "minishell_utils.h"

//lexical analize functions
int		lexical_analize(char *get_line);
int		set_sep(char *get_line, t_separators **separators);
int		tokenize(char *get_line, t_separators *separators, t_token **token);
int		append(t_separators **separators, int sep);
int		append_token(t_token **token, char *text, int sep);
int		word_len(char *get_line, char ch);
char	*fill_word(char **get_line, char ch);
int		fill_spaces(char **get_line, t_separators **separators);
int		fill_redirections(char **get_line, t_separators **separators);
int		fill_external(char **get_line, t_separators **separators);

//error functions
int	print_syntax_error(int c);
int	free_list(t_separators **separators);
int	check_quotes(t_separators *separators);
int	check_pipe(t_separators *separators);
int	check_redirections(t_separators *separators);
int	check_separators(t_separators *separators);

#endif