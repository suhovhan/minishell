#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_separators		*separators;
	// t_token				*token;

	char		*get_line;
	while (1)
	{
		while (1)
		{
			get_line = readline("minishell-$ ");
			add_history(get_line);
			if (!ft_strncmp(get_line, "exit", 4))
				return (0);
			set_sep(get_line, &separators);
			if (check_separators(separators) == -1)
			{
				free_list(&separators);
				break ;
			}
			// tokenize(get_line, separators, &token);
			
		}
	}
	return (0);
}
