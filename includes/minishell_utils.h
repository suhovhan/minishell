#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include "minishell_structs.h"

int		append(t_separators **separators, int sep);
int		word_len(char *get_line, char ch);
char	*fill_word(char **get_line, char ch);

#endif