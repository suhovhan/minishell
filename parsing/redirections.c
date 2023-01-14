/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:29:45 by suhovhan          #+#    #+#             */
/*   Updated: 2022/12/17 23:20:30 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_no_such_file_or_directory()
{
	printf("no such file or directory\n");
}

int	open_red_in(char *filename)
{
	int	fd;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_no_such_file_or_directory();
	else
		dup2(1, fd);
	close(fd);
	return (fd);
}
