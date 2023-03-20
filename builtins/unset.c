/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:12:32 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/19 23:55:31 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*Note that when you unset an environment variable or function using unset,
the change only affects the current shell environment and any child processes
that inherit the environment. It does not affect the parent process or any
other processes running on the system.*/

/*Add possibility to unset more than 1 variable at the time
Keep in mind that this function belongs to the parent since we need to
change the vec, and it only unsets variables if expressions->len == 1
Example: 'ls | unset MY_VAR' , does nothing*/

void	_unset(t_expression *expr, t_vec **env)
{
	t_vec	*temp_env;
	size_t	i;
	char	*var_name;
	char	*env_var;

	i = 0;
	var_name = expr->args.buf[1];
	temp_env = *env;
	while (i < temp_env->len)
	{
		env_var = temp_env->buf[i];
		if (ft_strncmp(var_name, env_var, ft_strlen(var_name)) == 0
			&& env_var[ft_strlen(var_name)] == '=')
		{
			vec_del(env, i);
			return ;
		}
		i += 1;
	}
}
