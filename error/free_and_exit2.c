/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhovhan <suhovhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 01:53:43 by suhovhan          #+#    #+#             */
/*   Updated: 2023/02/03 18:42:23 by suhovhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_mtx(char **mtx)
{
	int	i;

	i = -1;
	if (mtx)
	{
		while (mtx[++i])
		{
			free(mtx[i]);
			mtx[i] = NULL;
			mtx[i] = NULL;
		}
		free(mtx);
		mtx = NULL;
	}
}
