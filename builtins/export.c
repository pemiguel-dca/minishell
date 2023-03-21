/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:08:32 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/21 14:24:58 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Export funcionara no child so se nao tiver nenhum argumento.
Mas se tentarmos inicializar uma variavel da seguinte maneira "ls | export MY_VAR=hello" nao ira funcionar*/
/*Funciona com mais de um argumento, "export A=a B=b"*/
#include "builtins.h"

static void		print_export(t_vec *env)
{
	size_t	i;

	i = 0;
	while (i < env->len)
	{
		printf("declare -x %s\n", (char *)env->buf[i]);
		i += 1;
	}
}

static t_vec	copy_current_envs(t_vec *env)
{
	t_vec	copy;
	size_t	i;

	copy = vec_new();
	i = 0;
	while (i < env->len)
	{
		vec_push(&copy, ft_strdup(env->buf[i]));
		i += 1;
	}
	return (copy);
}

static void		organized_envs(t_vec *env)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	while (i < env->len)
	{
		j = 0;
		while (j < env->len - i - 1)
		{
			if (ft_strcmp((char *)env->buf[j], (char *)env->buf[j + 1]) > 0)
			{
				temp = env->buf[j];
				env->buf[j] = env->buf[j + 1];
				env->buf[j + 1] = temp;
			}
			j += 1;
		}
		i += 1;
	}
	print_export(env);
}

static int		create_vars(t_expression *expr, t_vec *env)
{
	size_t	i;

	i = 1;
	while (i < expr->args.len)
	{
		if (pos_env_var(env, (char *)expr->args.buf[i]) == -1)
		{
			if (!ft_isalpha(((char *)expr->args.buf[i])[0]))
			{
				printf("export: '%s': not a valid identifier\n", (char *)expr->args.buf[i]);
				return (1);
			}
			else if (ft_strchr((char *)expr->args.buf[i], '='))
				vec_push(env, ft_strdup(expr->args.buf[i]));
		}
		else
		{
			vec_del(&env, pos_env_var(env, (char *)expr->args.buf[i]));
			vec_push(env, ft_strdup(expr->args.buf[i]));
		}
		i += 1;
	}
	return (0);
}

int		_export(t_expression *expr, t_vec *env)
{
	size_t	i;
	t_vec	copy;
	int		exit_status;

	i = 1;
	copy = copy_current_envs(env);
	exit_status = 0;
	if (expr->args.len == 1)
		organized_envs(&copy);
	else
		exit_status = create_vars(expr, env);
	return (exit_status);
}

