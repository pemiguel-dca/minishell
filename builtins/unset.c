/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:12:32 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/22 22:19:11 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	free_vars(char **vars, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(vars[i]);
		i += 1;
	}
	free(vars);
}

static char	**get_var_names(const t_expression *expr)
{
	size_t	i;
	char	**var_names;

	i = 0;
	var_names = malloc(expr->args.len * sizeof(char *));
	while (i < expr->args.len - 1)
	{
		var_names[i] = ft_strdup(expr->args.buf[i + 1]);
		i += 1;
	}
	var_names[i] = 0;
	return (var_names);
}

size_t	_unset(t_expression *expr, t_vec **env)
{
	t_vec	*temp_env;
	size_t	i;
	size_t	j;
	char	**var_names;
	char	*env_var;

	temp_env = *env;
	var_names = get_var_names(expr);
	i = temp_env->len - 1;
	while (i != 0)
	{
		env_var = temp_env->buf[i];
		j = 0;
		while (j < expr->args.len - 1)
		{
			if (ft_strncmp(var_names[j], env_var, ft_strlen(var_names[j])) == 0
				&& env_var[ft_strlen(var_names[j])] == '=')
				vec_del(env, i);
			j += 1;
		}
		i -= 1;
	}
	free_vars(var_names, expr->args.len - 1);
	return (0);
}
