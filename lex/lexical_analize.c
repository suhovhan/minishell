#include "../includes/minishell.h"

int	lexical_analize(char *get_line)
{
	if (count_dquote(get_line) % 2)
		return (-1);
	if (count_quote(get_line) % 2)
		return (-1);
	return (0);
}