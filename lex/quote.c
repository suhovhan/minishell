#include "../includes/minishell.h"

int	count_dquote(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == _duble_quote)
			count++;
	return (count);
}

int	count_quote(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == _single_quote)
			count++;
	return (count);
}