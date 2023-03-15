/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envstuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:04:49 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/13 18:50:36 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer/lexer.h"
#include "../parser/parser.h"

t_list	*create_envs(char **envp)
{
	size_t	i;
	t_list	*env;

	env = NULL;
		i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&env, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	return (env);
}
