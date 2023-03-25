/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envstuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:04:49 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/25 18:08:12 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../libft/libft.h"

int	pos_env_var(t_vec *env, char *find)
{
	size_t	i;
	size_t	equal_sign;
	char	*env_var;

	i = 0;
	equal_sign = 0;
	while (find[equal_sign] && find[equal_sign] != '=')
		equal_sign += 1;
	while (i < env->len)
	{
		env_var = env->buf[i];
		if (ft_strncmp(find, env_var, equal_sign) == 0)
			return (i);
		i += 1;
	}
	return (-1);
}

void	set_env(t_vec **env, char *name, char *value)
{
	size_t	i;
	char	*new_env_var;
	char	*full_name;
	char	*new_var;

	i = pos_env_var(*env, name);
	full_name = ft_strjoin(name, "=");
	new_var = ft_strjoin(full_name, value);
	new_env_var = ft_strdup(new_var);
	vec_push(*env, new_env_var);
	free(new_env_var);
	free(full_name);
	free(new_var);
}

char	*get_var_value(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i += 1;
	i += 1;
	return (var + i);
}

t_vec	create_envs(char **envp)
{
	size_t	i;
	t_vec	env;

	env = vec_new();
	i = 0;
	while (envp[i])
	{
		vec_push(&env, envp[i]);
		i += 1;
	}
	return (env);
}
