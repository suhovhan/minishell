/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetrosy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:52:12 by mpetrosy          #+#    #+#             */
/*   Updated: 2022/12/15 17:35:01 by mpetrosy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include <stdlib.h>
#include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
/*
typedef struct s_env
{
	char			*key;
	char			*value;
	struct	s_env	*next;
}					t_env;

*/
typedef struct s_bin
{
	char	*path;
}				t_bin;

char	**ft_split(char const *s, char c);
int	ft_strcmp(char *s1, char *s2);

#endif