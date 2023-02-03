/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:41:55 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 18:46:06 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_no_such_file_or_directory(char *filename)
{
	printf("minishell: %s: No such file or directory\n", filename);
	return (1);
}

int	print_syntax_error(int c)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error ", 13);
	write(2, "near unexpected token `", 23);
	if (c == 1)
		write(2, "newline", 7);
	else
		write(2, &c, 1);
	write(2, "'\n", 2);
	return (0);
}

void	exit_shell(t_addres *addres, int exit_code)
{
	if (exit_code == _HEREDOC)
		printf("minishell: maximum here-document count exceeded\n");
	addres->exit_status = 2;
	addres->shlvl--;
	free_token(&addres->token);
	exit(addres->exit_status);
}
