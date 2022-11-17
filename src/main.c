#include "../includes/minishell.h"

void	print_shell()
{
	static int i = 0;
	if (i)
		printf("\e[1;34msuhovhan-$\e[0m");
	else
		printf("\e[1;35mmpetrosy-$\e[0m");
	if (i == 1)
		i = -1;
	i++;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char		*get_line;
	t_token		*tokend_line;

	while (1)
	{
		print_shell();
		get_line = readline(" ");
		add_history(get_line);
		if (!ft_strncmp(get_line, "exit", 4))
			return (0);
		get_token(&get_line, &tokend_line);
		while (tokend_line)
		{
			printf("token = [ %d ]\n", tokend_line->token);
			tokend_line = tokend_line->next;
		}
	}
	return (0);
}