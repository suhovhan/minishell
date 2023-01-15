/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetrosy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:40:29 by mpetrosy          #+#    #+#             */
/*   Updated: 2023/01/10 17:40:31 by mpetrosy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



void	ankap(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		
		printf("declare -x %s %s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

void	alph()
{

}