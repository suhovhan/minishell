/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:16:08 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/02/04 17:49:51 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(char	*cmd)
{
	char	*path;
	char	cwd[1024];

	(void)cmd;
	path = getcwd(cwd, sizeof(cwd));
	if (path)
	{
		ft_putstr_fd(path, 1);
		write(1, "\n", 1);
	}
	else
		perror("minishell-$");
}
