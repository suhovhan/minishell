/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:41:55 by suhovhan          #+#    #+#             */
/*   Updated: 2023/01/29 19:16:01 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
