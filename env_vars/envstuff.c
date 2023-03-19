/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envstuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:04:49 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/19 14:44:43 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../libft/libft.h"

t_vec	create_envs(char **envp)
{
	size_t	i;
	t_vec	env;

	env = vec_new();
	i = 0;
	while (envp[i])
	{
		vec_push(&env, ft_strdup(envp[i]));
		i += 1;
	}
	return (env);
}
