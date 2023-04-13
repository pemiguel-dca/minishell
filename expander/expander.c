/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:31:36 by pemiguel          #+#    #+#             */
/*   Updated: 2023/04/13 16:52:36 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	add_export(t_expression *expr)
{
	void	*temp;

	vec_push(&expr->args, ft_strdup("export"));
	temp = expr->args.buf[0];
	expr->args.buf[0] = expr->args.buf[expr->args.len - 1];
	expr->args.buf[expr->args.len - 1] = temp;
}

size_t	home_value(t_expression *expr, t_vec *env, size_t i)
{
	char		*find;

	find = ft_strdup(expr->args.buf[i]);
	free(expr->args.buf[i]);
	expr->args.buf[i] = ft_strdup(get_var_value(env->buf
			[pos_env_var(env, "HOME")]));
	free(find);
	return (0);
}

void	change_value(t_expression *expr, t_vec *env)
{
	size_t	i;

	i = 0;
	while (i < expr->args.len)
	{
		if (is_home(expr->args.buf[i]))
			home_value(expr, env, i);
		i += 1;
	}
}

void	expander(t_vec *expressions, t_vec *env)
{
	size_t			i;
	t_expression	*expr;

	i = 0;
	while (i < expressions->len)
	{
		expr = expressions->buf[i];
		if (is_expand_export(expr))
			add_export(expr);
		else
			change_value(expr, env);
		i += 1;
	}
}
