#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "minishell_structs.h"

//lexical analize functions
int		lexical_analize(char *get_line);
int		count_dquote(char *str);
int		count_quote(char *str);
int		get_token(char **get_line, t_token **tokened_line);
int		append(t_token **tokend_line, int sep);
int		word_len(char *get_line, char ch);
char	*fill_word(char **get_line, char ch);
int		fill_spaces(char **get_line, t_token **tokend_line);
int		fill_redirections(char **get_line, t_token **tokend_line);
int		fill_external(char **get_line, t_token **tokend_line);

#endif