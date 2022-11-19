#include "../includes/minishell.h"

int	free_list(t_separators **separators)
{
	t_separators *sep;
	
	while (*separators)
	{
		sep = *separators;
		(*separators) = (*separators)->next;
		free(sep);
	}
	return (0);
}