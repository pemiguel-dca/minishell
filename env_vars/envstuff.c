/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envstuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:04:49 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/20 22:37:03 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../libft/libft.h"
/*
static int pos_env_var(t_vec *env, char *find)
{
	size_t	i;
	char	*env_var;

	i = 0;
	while (i < env->len)
	{
		env_var = env->buf[i]; 
		if (ft_strncmp(find, env_var, ft_strlen(find)) == 0)
		i += 1;
	}
}

void	set_env(t_vec **env)
{
	
}
*/

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
