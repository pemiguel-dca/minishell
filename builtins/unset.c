/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:12:32 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/19 19:14:28 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*Note that when you unset an environment variable or function using unset,
the change only affects the current shell environment and any child processes
that inherit the environment. It does not affect the parent process or any
other processes running on the system.*/

/*Not working*/
void	_unset(t_expression *expr, t_vec *env)
{
	size_t	i;
	char	*var_name;
	char	*env_var;

	i = 0;
	var_name = expr->args.buf[1];
	printf("%s", var_name);
	while (i < env->len)
	{
		env_var = env->buf[i];
		if (ft_strncmp(var_name, env_var, ft_strlen(var_name)
			&& env_var[ft_strlen(var_name)] == '='))
		{
			printf("%s", env_var);
			vec_del(env, i);
			return ;
		}
		i += 1;
	}
}
